# Homepage

We are using [Docsify](https://docsify.js.org/) to generate this documentation on the fly from the Markdown files in `/docs` of the [repository](https://www.github.com/mhollfelder/openvent).\
Basically, writing documentation means adding additional Markdown files plus modifying Docsify settings if required.

The documentation here is served via Docsify and you are accessing the landing page.

## Folder and file structure

```console
docs/
┣ concept/          // The overall concept and generic explanation
┣ design/           // Design and communications related documentation
┣ getstarted/       // A Get Started guide
┣ knowledge/        // The knowledge hub around this topic
┣ mechanics/        // Documentation of the mechanical design
┣ prototype/        // Documentation of prototypes
┣ software/         // All software related documentation
┣ .gitkeep          // Keep this folder for Git even if empty
┣ .nojekyll         // Configure Jekyll for GitHub pages to not ignore files starting with underscore
┣ index.html        // Docsify index.html file for Docsify configuration
┣ README.md         // This README file
┗ _sidebar.md       // The sidebar for Docsify
```

## Disclaimer

:warning: We would like include a warning and disclaimer here:

Please check the full disclaimer as well before proceeding.

- The material and documentation here is provided with no warranties explicit or implied.
- No material on this site is intended to provide medical advice. All designs are intended for investigational use only.
- This site does not represent any official policies or procedures.

The project is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and noninfringement.\
In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the software.

Only use **this repository, designs, documentation or any provided information** if you accept the above disclaimer.

## Project description

:wave: Clearly, the first choice is **always** available, professional, certified medical equipment.

During the Corona (COVID-19) pandemic it became obvious that a lack of medical equipment can cause a severe impact.\
Often, also simple equipment and designs can be helpful as long as no professional equipment is available.

This documentation and repository contains generic information about an open-source ventilator device.\
Main purpose of this project is to build a ventilator when no professional and medical equipment is available.\
Easy to assemble and available components are used with a clear focus on simplicity, availability and scalability.

This project started as part of the hackathon [#WirvsVirus](https://wirvsvirushackathon.org/) of the German government.

## Current status

Right now, a prototype is in development with a bag valve mask, a 3D printed fixture and a motor.\
The prototype is tested and in an iterative, agile approach improved to provide a simple design.

## Development branches

We have the following components:

- `Concept`
- `Software`
- `Hardware`
- `Mechanics`
- `Documentation`

From the concept branch we merge information and drafts into the `Hardware`, `Software`, and `Mechanics` branch.\
Afterwards, we document the prototypes and the approach once all components come together in the `Document` branch.

## Development flow

We have a Slack channel for exchange on the overall development and exchange on the project itself.\
Moreover, we use GitHub [projects](https://github.com/mhollfelder/openvent/projects?query=sort%3Aname-asc+) to track the process, requirements, etc.

If you want to contribute, please open an issue, create a pull request or ping us at contact.openvent@gmail.com.

## Contributors

### Core team

The core team which started this project:

- [Mahmoud Ismail](https://github.com/mahmoudgo)
- [Nico Kelling](https://github.com/nicokelling)
- [Daniel Gernert](https://github.com/DanielGernert)
- [Alexander Maier](https://github.com/alex-km)
- [Manuel Hollfelder](https://github.com/mhollfelder)

### Additional contributors

So far, we have no additional contributors, but if you feel like contributing, please:

- Check out open action items or issues
- Fork the project
- Contribute to the repository
- Create a pull request

Additionally, please get in contact with us via contact.openvent@gmail.com for more details and the Slack channel.

## Similar projects

Here, we will add a list of similar projects which are worth being checked out.