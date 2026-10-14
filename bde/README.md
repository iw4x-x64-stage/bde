# bde - Demonware online services server for IW4x.

The `bde` executable serves Demonware online services that IW4x connects
to. It answers the authentication requests over HTTPS, accepts the lobby
service gateway connections, exchanges the bandwidth test packets over
UDP, and keeps its state in PostgreSQL.

## Usage

Run `bde --help` for the list of options.
