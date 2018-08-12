AllGamesCoin Core 0.2.0
===============================


http://allgamescoin.org


What is AllGamesCoin?
----------------

AllGamesCoin(XAGC) is a new cryptocurrency that provides a blockchain revolution for the gaming industry. We aim to use the blockchain to storage the game asset; to build trusty game rules; to achieve game economy system interoperability and player autonomy.

With the reshaping of the blockchain, the game equipment will become a real asset, the game token will also be truly valuable, and the rules of the game will be transparent and feasible. The blockchain will have a huge impact on the existing gaming system. It will quicken the pace of the gaming industry 4.0 era.

Blockchain technology will be applied to the following situations: game asset trading platform, game asset blockchain storage, rule identification, economic system interoperability, and player autonomy.

The AllGameCoin System adopts a three-layer structure of a public blockchain layer, a data blockchain layer and an application layer. The public blockchain adopts the consensus mode of POW and Masternode, the data blockchain adopts the consensus mode of super nodes, and the data blockchain will be authenticated twice in the public blockchain. The separation of the public blockchain and the data blockchain achieves the consensus of the whole users and the confirmation within several milliseconds.

AllGameCoin System will allow game developers and players that from all around the world to enjoy the tremendous changes and benefits of the blockchain rebuilding game world. XAGC holders will influence and manage the game world.

For more information, as well as an immediately useable, binary version of
the AllGamesCoin Core software, see http://allgamescoin.org/.


License
-------

AllGamesCoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is meant to be stable. Development is normally done in separate branches.
[Tags](https://github.com/allgamescoindev/allgamescoin/tags) are created to indicate new official,
stable release versions of AllGamesCoin Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](/doc/unit-tests.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

The Travis CI system makes sure that every pull request is built for Windows
and Linux, OS X, and that unit and sanity tests are automatically run.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
