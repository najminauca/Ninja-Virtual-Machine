#!/usr/bin/env bash

# This function optionally prepends sudo to commands on systems where it exists.
# On some platforms (i.e. an ubuntu docker container) there is no unprivileged user and thus no sudo.
function prepend_sudo() {
  if [ -x "$(command -v sudo)" ]; then
    echo "sudo $*"
  else
    echo "$*"
  fi
}
function exiting() {
  echo "[Bootstrap] Exiting." && exit 1
}

function get_package_manager() {
  local
  if [ -x "$(command -v apt)" ]; then
    echo "apt"
  else echo ""; fi
}

function run_command() {
  echo "[Bootstrap] Trying to run '$*'."
  read -p "[Bootstrap] Do you want to run this command now? [yN]" -n 1 -r
  echo # move to a new line
  if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "[Bootstrap] Permission to run a command refused."
    echo "[Bootstrap] You need to install the missing dependencies manually or give permission to the script to do it for you."
    exiting
  fi

  echo "[Bootstrap] Running '$*'"
  if [[ $* == *"sudo"* ]]; then echo "[Bootstrap] You may be asked for your root password."; fi
  eval "$*"
}

PACKAGE_MANAGER=$(get_package_manager)

function exit_unrecognized_package_manager() {
  echo "[Bootstrap] I can't help you fix this because I do not recognize your package manager."
  echo "[Bootstrap] You may need to install some dependencies yourself."
  exiting
}

function try_to_remedy_failing_package_installation() {
  local COMMAND
  case $PACKAGE_MANAGER in
  "apt")
    COMMAND=$(prepend_sudo "apt update")
    ;;
  *)
    exit_unrecognized_package_manager
    ;;
  esac

  echo "[Bootstrap] Trying to fix installation issues for you."
  if ! run_command "$COMMAND"; then
    echo "[Bootstrap] Trying to fix installation issues failed again. I'm giving up."
    exiting
  fi
}

function install_package() {
  echo "[Bootstrap] Missing package(s) '$*'."

  # Try to identify the system package manager. Currently only recognizes apt.

  local COMMAND
  case $PACKAGE_MANAGER in
  "apt")
    COMMAND=$(prepend_sudo "apt install -y $*")
    ;;
  *)
    exit_unrecognized_package_manager
    ;;
  esac

  echo "[Bootstrap] Package manager identified, attemping automated installation of the missing packages."
  if ! run_command "$COMMAND"; then
    echo "[Bootstrap] Automated package installation failed."
    try_to_remedy_failing_package_installation

    if ! run_command "$COMMAND"; then
      echo "[Bootstrap] Automated package installation failed again. I'm giving up."
      echo "[Bootstrap] You may need to install dependencies manually."
      exiting
    fi
  fi

  echo "[Bootstrap] Automated package installation successful."
}

function install_pip_package() {
  echo "[Bootstrap] Missing pip-package(s) '$*'."
  echo "[Bootstrap] Attemping automated installation of the missing packages."
  local COMMAND="pip3 install $*"

  if ! run_command "$COMMAND"; then
    echo "[Bootstrap] Automated python package installation failed."
    echo "[Bootstrap] You may need to install dependencies manually."
    exiting
  fi

  echo "[Bootstrap] Automated python package installation successful."
}

function ensure_needed_executables_are_installed() {
  if ! command -v python3 &>/dev/null || ! command -v pip3 &>/dev/null; then
    install_package python3 python3-pip
  fi

  if ! command -v pipenv &>/dev/null; then
    echo "[Bootstrap] Pipenv is not installed on your system and needed for this script."
    echo "[Bootstrap] Pipenv is a tool to manage virtual python environments and its use prevents having to install dependencies directly on your system."

    install_pip_package pipenv
  fi
}

ensure_needed_executables_are_installed

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")

cd "$SCRIPTPATH" || exit

echo "[Bootstrap] Running 'pipenv install' to ensure the existence of a virtual environment."
echo "[Bootstrap] This may take a moment."
if ! (pipenv install); then
  echo "[Bootstrap] Installing script dependencies with 'pipenv install' failed."
  exiting
fi

echo "[Bootstrap] Running the script in a virtual environment."
pipenv run python3 ./main.py
