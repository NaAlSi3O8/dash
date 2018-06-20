
Debian
====================
This directory contains files used to package allgamescoind/allgamescoin-qt
for Debian-based Linux systems. If you compile allgamescoind/allgamescoin-qt yourself, there are some useful files here.

## allgamescoin: URI support ##


allgamescoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install allgamescoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your allgamescoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/allgamescoin128.png` to `/usr/share/pixmaps`

allgamescoin-qt.protocol (KDE)

