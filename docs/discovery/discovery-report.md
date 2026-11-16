# Discovery report
## Problem statement
A Los Angeles animation studio needs to render a 90-minute HD film at 24 frames per second on its farm of up to 100 CPU-only machines within two months, using software its own team can understand, debug and extend, because its last in-house renderer produced unexplained black artefacts that doubled render times and delayed delivery by three weeks, but the only person who understood that code has left and the commercial replacement costs over $2 million in licences and cannot be modified.
## Client interview summary
### Reliability and debuggability
**Need:** The studio needs a renderer whose images are reproducible and whose anomalies can be traced to a cause and fixed.
> **Q (a classmate):** "Can you share the last time your rendering tool broke?"
>
> **A:** "The last time our rendering broke, and this is why we opened up this project, was about 6 months ago. We had a big project to bring to publication and we kept finding that there were black artefacts in the images that were produced, and the rendering time doubled. [...] Our engineering team couldn't figure out why we were having these anomalies, plus it was going slower, and in the end we ended up having to buy a commercial license that cost us a lot of money for a professional rendering system, and we delivered three weeks late."

> **Q (a classmate):** "What will demonstrate that the new [ray tracer] will fit your needs?"
>
> **A:** "I think there are two elements. One, it produces a reliable image. So if I give it some inputs, I can always expect the same output. And the second one is that if there is an image problem, an anomaly, we can figure out [...] why there is that anomaly, and what steps we can take to correct it. [...] That is our biggest frustration."

**My conclusion:** Success is defined by reproducibility and diagnosability, not by features. Since path tracing relies on random sampling, "same input, same output" means the randomness must be seeded and controlled, and anomalies must be caught by automated tests (for example comparisons with reference images) before they reach production.

### Maintenance and knowledge loss
**Need:** The studio's own team must be able to understand, debug and evolve the code for years, even after its authors leave.
> **Q (a classmate):** "I'd like to know, after conceiving the solution, who will maintain it? What skills do they have, let's say, in five years afterwards?"
>
> **A:** "We would like to maintain the solution in-house. And we would like to be able to maintain it in the long term. So it must be a solution that is maintainable."

> **Q (me):** "Is there any information that we need but we didn't ask?"
>
> **A:** "[...] what happens when the person who wrote it leaves the team? [...] The person who wrote the software left our team already. And we found these artifacts and no one could tell me why we had them. [...] If one of my team members leaves, can the other team members continue to understand and use this code in the long term? [...] We had a team of five people. But the key person who wrote it left. And even the five people, they didn't know how to debug."

**My conclusion:** The root cause of the last failure was knowledge concentrated in one person, not only a bug. Readable code, tests, documentation and recorded design decisions are therefore part of the product, not extras.

### Extensibility
**Need:** The studio needs to add its own features (shapes, effects) without waiting for a vendor.
> **Q (a classmate):** "So I'd like to know what do you render with today?"
>
> **A:** "So today, well [...] before we had our in-house solution that had the bugs and then we had to go to a commercial solution which was Maya."

> **Q (a classmate):** "Is there a feature that you need in your new software that you don't have with Maya?"
>
> **A:** "I would say the main thing is the ability to add our own features. With Maya the problem is the license is very expensive and if we want to add something specific we have to go through official channels of Maya and either they just say no or it will take six months or a year to add a feature. Which means we are limited in [our] creativity to only what Maya can produce."

> **Q (me):** "Do you have requirements for [the] rendering feature[s]?"
>
> **A:** "The requirements change constantly with every new project because every new film we try and push the boundaries. So we need a tool that can accept these new requirements."

**My conclusion:** The architecture must be open to extension: adding a new shape or material should not require modifying the core of the renderer.

### Cost
**Need:** The studio needs to stop paying per-seat and per-node licences that made its last film unprofitable.
> **Q (a classmate):** "So actually you said that you are using a ray tracer that is on the market and it's just, it does not fit your expectations or it's just the price?"
>
> **A:** "It is, it is very expensive. So our last project we made a loss because the licenses were so expensive that we couldn't afford it. And it also doesn't satisfy all the needs that we have for our future projects. So in the last project we had to sacrifice some [features]."

> **Q (a classmate):** "What did you spend on [...] last year [...]?"
>
> **A:** "We must have spent over 2 million dollars for the licenses. [...] The license is [seat]-based. So normally we pay per machine, per artist. Plus, every single node in our render [farm], we have to pay an individual license for. Which is why this is a huge budget. We'd like to in-house it, which makes it much more affordable."

> **Q (a classmate):** "Do you have a budget for this project?"
>
> **A:** "Yes. So we would like to spend no more than 500,000 euro on the project. [...] There will be extra budget for the development team that we will be hiring, but we expect this investment will be cheaper in the long term."

**My conclusion:** This confirms the state of the art: commercial renderers charge per node, so a 100-machine farm multiplies the cost. Owning the renderer turns a recurring licence cost into a one-off development cost plus maintenance.

### Performance and scale
**Need:** A 90-minute HD film must be rendered on the existing CPU farm within two months.
> **Q (a classmate):** "But what is the size of your project? Is it like 4K, is it 10 minutes, 90 minutes?"
>
> **A:** "It's a 90 minute feature film at HD." [later:] "We render at 24 frames per second."

> **Q (me):** "How [big] is your farm?" [...] "And what is your deadline to create a movie?"
>
> **A:** "We have up to 100 machines." [...] "Typically once the creative side is done, you don't want to spend any more than two months for rendering, the final rendering."

> **Q (a classmate):** "What kind of hardware specs do you have in your company?"
>
> **A:** "[...] We don't have graphics [cards] so everything must be rendered by the CPU."

**My conclusion:** 90 min × 60 s × 24 fps = 129,600 frames. Two months is about 1,440 hours, so 100 machines give about 144,000 machine-hours: the final render can take at most about 66 minutes per frame per machine, assuming the farm does nothing else and each frame is rendered once. With no GPUs, the renderer has to use every CPU core (multithreading) and spread frames across machines.

### Preview speed versus final quality
**Need:** Designers need fast, reasonably accurate previews; the final render needs high quality.
> **Q (a classmate):** "What is more important, realistic image or fast image?"
>
> **A:** "I'd say it depends. For the designer, a fast image, which is pretty accurate, is very important. [...] We don't want him to wait too long to see what the result of his work is. But in the final scene, a high quality image is very important."

> **Q (me):** "And how many pre-renders do you have?"
>
> **A:** "Typically at least 10 different pre-renders per image."

**My conclusion:** Quality must be a setting of the same renderer (resolution, samples per pixel, bounce depth), not two different tools. With at least 10 pre-renders per image, preview speed matters as much as final quality.

### Workflow, inputs and outputs
**Need:** A command-line renderer that reads a scene file and writes images, with no user interface.
> **Q (me):** "Do you need the [ray tracer] to connect directly to that software or can you read the file instead?" [...] "So do you need an interface?"
>
> **A:** "You can definitely read the file." [...] "No. Typically what happens is that a standard file will be created, saved by the designer, and this file will be put onto the render [farm] and just the process is launched to render it. No interface is required."

> **Q (a classmate):** "How do the designer[s] or graphics [artists] receive the images?"
>
> **A:** "Okay, so the designer will use some third party software to position the scene. To put objects in the scene and set up lighting. Typically then they'll save a file. And that file will be the input to your [ray tracer]. [...] These images will just be saved to a disk and then sequenced into a film. Or just that we can consult one by one."

> **Q (me):** "Do you want a software to render frames or to create frames?"
>
> **A:** "No, we just want to render. So it's a black box that takes a description of the scene and outputs an image."

> **Q (me):** "[Does the ray tracer] must support [a] specific format?"
>
> **A:** "I'll let you decide that. But it must be a standardized format that we can use [...]."

> **Q (me):** "So to be clear, you don't want an extension with it to import your own model?" [...] "And which extension do you use, [finally]?"
>
> **A:** "Ah, perhaps. That would be very useful." [...] "Whatever [...] extension the current software can support." [...] "I will [ask] my graphics team to see what they use."

**My conclusion:** The renderer is a batch tool: scene file in, image files out, saved one file per frame. The choice of a standard scene format is left to us, but the client does not yet know which format its designers' software exports.

### Scope and deadline
**Need:** A first version rendering simple primitives, ready by 5 January.
> **Q (a classmate):** "Do you have requirements for [the] rendering feature[s]?"
>
> **A:** "[...] For the moment let's just say we need to be able to [render] spheres, planes, and that's it for now." [...] "The software must be delivered by January the 5th."

> **Q (a classmate):** "When do we need the [production]?" [...] "Then what must it be?"
>
> **A:** "[...] Must be ready for the 5th of January." [...] "It must have the full ray tracer capable of producing images for a full film within a two-month period."

> **Q (me):** "And which technique is the most used? Is it a simulation of fogs, textures?"
>
> **A:** "For the moment we are just going to start off with [...] ray tracing. Just ray tracing for the moment. That's the most urgent for our next project. But we would like the software to be able to include new effects, new shapes, new..."

**My conclusion:** The first delivery covers ray tracing of spheres and planes, but it must already meet the performance target and be designed so that new shapes and effects can be added later.

### Type of content
**Need:** The renderer is for full-length animated films rather than live-action visual effects.
> **Q (a classmate):** "Can you tell me what kind of content do you render? Like full animation or live action effects?"
>
> **A:** "It's mainly full animation. And I'd say the most similar is Toy Story."

**My conclusion:** The target is a complete computer-generated image, not effects composited over filmed footage. This sets the expected quality level: stylised animation in the spirit of Toy Story rather than photorealism.

### Open source and contributions
**Need:** Partner studios must be able to propose changes, while the studio keeps control of what is accepted.
> **Q (a classmate):** "Do other studios use the same programming language?"
>
> **A:** "Yes. [...] We do rely on partners to do the rendering for us. And these partners have skill sets to contribute to this project as well."

> **Q (a classmate):** "How will you review and who will review and [accept] the contribution?"
>
> **A:** "We'll maintain the responsibility in-house. But we would like a way for them to contribute [...] proposed changes."

> **Q (a classmate):** "Do you have rules or a [style guide] for the code?"
>
> **A:** "Not especially, no. We rely on you for that."

**My conclusion:** We have to define the contribution process ourselves: coding rules, a contribution guide and a review step owned by the studio.

### Documentation
**Need:** Technical documentation for the studio's developers, and a user guide for artists and farm operators.
> **Q (a classmate):** "Do you need documentation in [a] specific format?"
>
> **A:** "No. [I'll] let you provide that. We do have a development team which will take ownership of what you make for us. So there will be technical people reading it. However, we expect some kind of user guide for the [graphic] artists or the people setting up the render [farm]."

**My conclusion:** There are two audiences with different needs: developers (architecture, design decisions, how to contribute) and users (how to describe a scene and launch a render).

### Open questions
- **Current tool:** the client said the commercial solution was "Maya", which is a 3D creation application rather than a renderer (its bundled renderer is Arnold). Which renderer was actually used?
- **Scope contradiction:** "spheres, planes, and that's it for now" versus "the full ray tracer capable of producing images for a full film" by 5 January, and importing their own models "would be very useful". What exactly is expected on 5 January?
- **Scene format contradiction:** "I'll let you decide" and "a standardized format" versus "whatever [...] the current software can support" and "I will ask my graphics team". Which format do the designers' tools export?
- **Pre-renders:** do the 10 pre-renders per image run on the same farm, inside or before the two-month window? If they share the farm, the time budget per frame drops sharply.
- **Resolution:** "HD" could mean 1280×720 or 1920×1080, which changes the pixel count by 2.25×.
- **Farm:** how many CPU cores per machine, and is the farm dedicated to final rendering?
- **Reproducibility:** does "the same output" mean bit-identical images, or visually identical ones?
- **Open source:** will the code be public, or shared only with partner studios? (In the recording it is unclear who said "all the code will be open sourced".)
- **Output:** which image file format is expected for the final frames?
- **Currencies:** licences were quoted at "over 2 million dollars" and the budget at "500,000 euro", described as "about one quarter": the comparison mixes currencies.
- **Missing parts of the recording:** the start of the interview and the passage around 10:48 were not captured.
## State of the art
| Solution | Maker | Licence | Pricing (date checked) | Capabilities | Sources |
|---|---|---|---|---|---|
| RenderMan | Pixar Animation Studios | Proprietary (free Non-Commercial edition) | $595 per licence, perpetual, + $250/yr maintenance; one licence = one artist seat or one farm node (2026-11-16) | CPU path tracing (RIS) and CPU+GPU (XPU); USD/Hydra; MaterialX, OSL; ML denoiser; Tractor farm manager included | [RenderMan store](https://renderman.pixar.com/store) |
| Arnold | Autodesk | Proprietary, subscription only | $430/yr or $55/month per user; farm/batch pricing not published (2026-11-16) | CPU and GPU path tracing; USD/Hydra; MaterialX, OSL; OptiX/OIDN denoising | [Autodesk Arnold – Buy](https://www.autodesk.com/products/arnold/buy) |
| V-Ray | Chaos | Proprietary, subscription | Solo €474/yr, Premium €706.80/yr, Collection €1,138.80/yr (EU list prices excl. VAT, before a temporary -20% promotion); Enterprise and render-node pricing not published (2026-11-16) | CPU and GPU hybrid path tracing; USD/Hydra; MaterialX, OSL; denoising; Chaos Cloud rendering | [Chaos pricing](https://www.chaos.com/pricing#vray) |
| Redshift | Maxon | Proprietary, subscription (also in Maxon One) | €298.80/yr or €50.40/month (EU prices incl. VAT); Teams and render-node pricing not published (2026-11-16) | Biased, GPU-first renderer (CUDA/Metal/HIP) with CPU mode; USD/Hydra; OSL (limited); denoising | [Maxon – Buy](https://www.maxon.net/en/buy) |
| Karma | SideFX | Proprietary, bundled with Houdini | Houdini Indie $299/yr (2 Karma, $100K revenue cap), Core $1,475/yr (5 Karma), FX $3,505/yr (5 Karma); extra Karma $195/yr; bundled Karma licences usable on the farm (2026-11-16) | Karma CPU and Karma XPU (CPU+GPU); USD/Solaris-native; MaterialX, VEX/OSL; OptiX/OIDN denoising | [SideFX – Buy](https://www.sidefx.com/buy/) |
| Cycles | Blender Foundation | Apache 2.0 (standalone); GPL inside Blender | Free (2026-11-16) | CPU and GPU path tracing (CUDA/OptiX, HIP, Metal, oneAPI); Hydra delegate; OSL; OIDN/OptiX denoising | [Cycles LICENSE](https://github.com/blender/cycles/blob/main/LICENSE), [Blender COPYING](https://github.com/blender/blender/blob/main/COPYING) |
| pbrt-v4 | M. Pharr, W. Jakob, G. Humphreys | Apache 2.0 | Free (2026-11-16) | Research/teaching spectral renderer (path tracing, BDPT, MLT); CPU and GPU (CUDA/OptiX); documented line by line in the book *Physically Based Rendering* | [pbrt-v4 LICENSE](https://github.com/mmp/pbrt-v4/blob/master/LICENSE.txt) |
| Mitsuba 3 | EPFL Realistic Graphics Lab | BSD-3-Clause | Free (2026-11-16) | Research renderer on Dr.Jit (CPU/LLVM, GPU/CUDA); differentiable/inverse rendering; spectral and polarized modes | [Mitsuba 3 LICENSE](https://github.com/mitsuba-renderer/mitsuba3/blob/master/LICENSE) |

Almost every solution offers the same core: path tracing on CPU and GPU, USD/Hydra support, MaterialX/OSL shading and denoising. The five commercial renderers (RenderMan, Arnold, V-Ray, Redshift, Karma) are proprietary and priced per seat or per node, so the cost of a whole film grows with the size of the farm, three of them do not publish farm pricing, and none of them gives the studio access to the source code, which is exactly the dependency the client wants to escape. The open-source renderers remove both problems: they are free, and their permissive licences (Apache 2.0, BSD-3) let the studio read, fix, fork and keep the code. pbrt-v4 and Mitsuba 3 are built for research and teaching rather than film production, so Cycles is the closest match: Apache 2.0 as a standalone library, production-tested and usable outside Blender through Hydra. Its limit for this client is governance rather than licence: its roadmap is set by the Blender project, so the studio and its partners would depend on someone else's priorities or have to maintain a fork. Whether that is acceptable, compared with building and owning a new renderer, is a question for the client.
## What is ray tracing?
Ray tracing is a rendering technique that simulates the path of light as it bounces off surfaces in a scene. It takes a description of the scene (objects, materials, lights) and a camera as input, and outputs an image: a grid of coloured pixels. It can simulate global illumination and produce photo-realistic images of complex scenes, which is why it is used in film production and, increasingly, in games, where it complements or replaces traditional rasterization techniques. Basically, it works by tracing rays from the camera through each pixel of the image, several times per pixel through a sampling process. Each time a ray touches a surface, the material decides how much of the light is absorbed and in which direction the ray bounces, and the process continues recursively until the ray hits the sky, a light source or a maximum number of bounces; the colour of the pixel is the product of these absorptions along the path, averaged over all the samples. In theory, we could follow the light from the light sources to the camera, which is how light behaves in real life. However, no computer could afford it, because most of that light never reaches the camera, so we reverse the process, from the camera to the light sources, to avoid useless calculations for light we would never see.

**Sources:** I started from the video [How Ray Tracing (Modern CGI) Works And How To Do It 600x Faster](https://www.youtube.com/watch?v=gsZiJeaMO48) (Josh's Channel), and the reference I would come back to is [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) (Shirley, Black, Hollasch, 2025) and the rest of the series on [raytracing.github.io](https://raytracing.github.io/).
## What is C++?
### Programming paradigms
C++ is a programming language that evolved from C. It combines high-level abstractions with low-level control, which gives it high speed, and it has a really good longevity. C++ is a new language for me, but I have foundations in real-time programming and in object-oriented programming, which, whatever the language, let me understand what I am doing.
### What to watch out for
Unlike JavaScript, C++ has no garbage collector, so I have to think about how long each object lives. If I create a sphere as a local variable while building the scene and the world only keeps a pointer to it, the sphere is destroyed when the scene has been built, and its pointer then points to freed memory. With `make_shared`, the sphere is stored in memory that is only released when nothing holds it anymore, for example when it leaves the world.
### Shaping the domain model
No operation should be allowed between a `point3` and a `color`, because in context they represent two different things.

**Sources:** I started from explanations given by an AI assistant (Claude) and from the C++ used in [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). The reference I would come back to is [Learn C++](https://www.learncpp.com), and later the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).
