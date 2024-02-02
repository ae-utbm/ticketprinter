<img align="left" src="https://github.com/ae-utbm/sith4/assets/49886317/6f4e5eb6-ab48-4535-8cb4-8b1335b70d81" height="128">

# Ticket Printer v2

[![Discord](https://img.shields.io/badge/Discord-%235865F2.svg?style=for-the-badge&logo=discord&logoColor=white)](https://discord.gg/XK9WfPsUFm)
[![GitHub issues](https://img.shields.io/github/issues/ae-utbm/ticketprinter?style=for-the-badge)](https://GitHub.com/ae-utbm/ticketprinter/issues)
[![GitHub pull requests](https://img.shields.io/github/issues-pr/ae-utbm/ticketprinter?style=for-the-badge)](https://GitHub.com/ae-utbm/ticketprinter/issues)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/ae-utbm/ticketprinter?style=for-the-badge)](https://github.com/ae-utbm/ticketprinter/releases)

<br>

## Install

Clone the repo and install dependencies:

```bash
git clone https://github.com/ae-utbm/ticketprinter
pnpm install
```

**Having issues installing? See the Electron React Boilerplate [debugging guide](https://github.com/electron-react-boilerplate/electron-react-boilerplate/issues/400).**

## Starting Development

Start the app in the `dev` environment:

```bash
pnpm start
```

## Packaging for Production

To package apps for the local platform:

```bash
pnpm package
```

## About Electron React Boilerplate

- [Docs and guides here](https://electron-react-boilerplate.js.org/docs/installation)
- [Github repository](https://github.com/electron-react-boilerplate/electron-react-boilerplate)
- [Discord](https://discord.gg/Fjy3vfgy5q)

## Reason for rewrite

The decision to switch from Qt to Electron with React was primarily driven by two factors.

Firstly, Qt was too heavy to install, which made it challenging for users to set up and use the ticket printer software. Electron, on the other hand, provides a "lightweight" and easy-to-install framework, making it more accessible for users.

Secondly, the previous version of the ticket printer only worked on Linux, which required the Student Association to keep specific computers dedicated to running the software. By adopting Electron with React, the ticket printer can now run on multiple platforms, including Windows and macOS, eliminating the need for separate hardware setups.

Overall, the switch to Electron with React improved the installation experience and expanded the software's compatibility, making it more convenient and versatile for users.

## License

MIT © [Electron React Boilerplate](https://github.com/electron-react-boilerplate)
