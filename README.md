# cpp-dopewars
4th try now, because i broke github and vs

cpp-dopewars is a game focusing on buying and selling drugs.

note: the process of drug dealing may be illegal where you live. this game is purely fictional

## DLC Support
cpp-dopewars loads in DLCs with DLL importing. To start the game with DLC, you need to specify the DLC's DLL file in the command line arguments.

```cmd
dope-wars.exe opium.dll
```

The base game has no anti-piracy measures in place, but my DLC (Opium) does. It pings my [server](https://penguin2233.gq/projects/cpp-dopewars/key.php) with the key encoded in URL parameters. I go into more detail on my website [here](https://penguin2233.gq/projects/cpp-dopewars).

You can make your own DLCs as well, Opium's code is in the "opium" folder.

### But why anti-piracy? It sucks anyway
Why not? This is just a test project that I use to learn new programming concepts.

## Features
- Soundtrack, loads resource.bin with BASS audio library
- DLC support, function loading from DLLs
- Pings server for anti-piracy checking (Opium DLC only)
- Loan system
- Save and Load functions that can be DLC-aware
