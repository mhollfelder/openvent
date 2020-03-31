# :page_with_curl: System overview

## System diagram

An overview of the basic system components can be found in the following system diagram.
The overall system is split into the following high-level blocks:

- Mechanics
- Hardware peripherals
- Core hardware
- Software

These overarching blocks are broken each broken down to sub-components.\
Currently, work and documentation is also split along these dimensions and blocks.

| Mechanics        | Hardware peripherals      | Core hardware           | Software      |
| ---------------- | ------------------------- | ----------------------- | ------------- |
| Pneumantics      | User interaction elements | Microcontroller         | Base system   |
| Motor            | Sensing                   | Communication interface | Safety logics |
| Compression unit | Power supply              |                         | Control logic |
| Bag valve mask   | Motor power stage         |                         | Algorithms    |
| Fixture          | Motor control             |                         |               |

Please check our development flow here to see how these components are developed and synced to each other

## Bill of Material (BOM) selection

The BOM for the device depends on the respective prototype.\
Please check out the respective prototype pages as well for more information.\

The BOM of the latest prototype can be found [here](./prototype/latest.md).

