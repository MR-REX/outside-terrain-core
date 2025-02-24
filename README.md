# Outside Terrain Core

**Outside Terrain Core** is a modification for **Arma Reforger** that enables the rendering of **pre-generated outside terrain**
beyond the boundaries of the main map. This terrain is composed of specialized entity chunks, which are mesh objects
that can also be physical, allowing players and vehicles to traverse them seamlessly.

## Features

- **Visual Outside Terrain.** Render terrain beyond the main map using pre-generated mesh chunks.
- **Physical Outside Terrain.** Entity chunks can be physical, allowing players and vehicles to interact with the outside terrain.
- **Seamless Integration.** Designed to work seamlessly with Arma Reforger's existing systems and other mods.
- **Optimized Performance.** Using chunks for large-scale terrain.
- **Workshop Ready.** Published and available for use in the Arma Reforger Workshop.

## Usage

### For Players

Once installed, the mod will automatically render the pre-generated outside terrain when you load a compatible map.

### For Developers

To create custom outside terrain for your map, use the [Outside Terrain Tool](https://github.com/MR-REX/outside-terrain-tool)
for World Editor. This tool allows you to generate and save outside terrain chunks data to entity layer file, which can then
be integrated into your Arma Reforger map.

## How It Works

The mod uses entity chunks to represent the outside terrain. Each chunk is a mesh object that can be:
- **Rendered:** Displayed as part of the terrain.
- **Physical:** Enabled for collision and interaction with players and vehicles.

These chunks are pre-generated and placed in the game world, extending the playable area beyond the main map.

## License

This project is licensed under the **Arma Public License Share Alike (APL-SA)**. See the
[LICENSE](https://github.com/MR-REX/outside-terrain-core/blob/main/LICENSE) file for details.

## Acknowledgments

A special thanks to **Bohemia Interactive** for creating Arma Reforger.

## Support and Feedback

If you encounter any issues or have suggestions for improvement, please
[open an issue](https://github.com/MR-REX/outside-terrain-core/issues) on GitHub.

## Links

- [Arma Reforger Workshop Page](https://reforger.armaplatform.com/workshop/61F0D506562D9BC9-OutsideTerrainCore)
- [Outside Terrain Tool](https://github.com/MR-REX/outside-terrain-tool)