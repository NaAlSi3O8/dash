Sample init scripts and service configuration for allgamescoind
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/allgamescoind.service:    systemd service unit configuration
    contrib/init/allgamescoind.openrc:     OpenRC compatible SysV style init script
    contrib/init/allgamescoind.openrcconf: OpenRC conf.d file
    contrib/init/allgamescoind.conf:       Upstart service configuration file
    contrib/init/allgamescoind.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three Linux startup configurations assume the existence of a "allgamescoincore" user
and group.  They must be created before attempting to use these scripts.
The OS X configuration assumes allgamescoind will be set up for the current user.

2. Configuration
---------------------------------

At a bare minimum, allgamescoind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, allgamescoind will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that allgamescoind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If allgamescoind is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running allgamescoind without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/allgamescoin.conf`.

3. Paths
---------------------------------

3a) Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/allgamescoind`  
Configuration file:  `/etc/allgamescoincore/allgamescoin.conf`  
Data directory:      `/var/lib/allgamescoind`  
PID file:            `/var/run/allgamescoind/allgamescoind.pid` (OpenRC and Upstart) or `/var/lib/allgamescoind/allgamescoind.pid` (systemd)  
Lock file:           `/var/lock/subsys/allgamescoind` (CentOS)  

The configuration file, PID directory (if applicable) and data directory
should all be owned by the allgamescoincore user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
allgamescoincore user and group.  Access to allgamescoin-cli and other allgamescoind rpc clients
can then be controlled by group membership.

3b) Mac OS X

Binary:              `/usr/local/bin/allgamescoind`  
Configuration file:  `~/Library/Application Support/AllGamesCoinCore/allgamescoin.conf`  
Data directory:      `~/Library/Application Support/AllGamesCoinCore`
Lock file:           `~/Library/Application Support/AllGamesCoinCore/.lock`

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start allgamescoind` and to enable for system startup run
`systemctl enable allgamescoind`

4b) OpenRC

Rename allgamescoind.openrc to allgamescoind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/allgamescoind start` and configure it to run on startup with
`rc-update add allgamescoind`

4c) Upstart (for Debian/Ubuntu based distributions)

Drop allgamescoind.conf in /etc/init.  Test by running `service allgamescoind start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

4d) CentOS

Copy allgamescoind.init to /etc/init.d/allgamescoind. Test by running `service allgamescoind start`.

Using this script, you can adjust the path and flags to the allgamescoind program by
setting the ALLGAMESCOIND and FLAGS environment variables in the file
/etc/sysconfig/allgamescoind. You can also use the DAEMONOPTS environment variable here.

4e) Mac OS X

Copy org.allgamescoin.allgamescoind.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.allgamescoin.allgamescoind.plist`.

This Launch Agent will cause allgamescoind to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run allgamescoind as the current user.
You will need to modify org.allgamescoin.allgamescoind.plist if you intend to use it as a
Launch Daemon with a dedicated allgamescoincore user.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
