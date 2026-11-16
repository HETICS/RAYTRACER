# Discovery report
## Problem statement
[TODO: one sentence, chosen after the interview — format "[Client] needs [what] because [why], but [obstacle]".]
## Client interview summary
### [TODO: Theme]
**Need:** [TODO]
> **Q ([TODO: who asked]):** "[TODO]"
>
> **A:** "[TODO]"

**My conclusion:** [TODO]
### Open questions
- [TODO]
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
[TODO: one paragraph, in your own words.]
**Sources:** [TODO]
## What is C++?
### Programming paradigms
[TODO]
### What to watch out for
[TODO]
### Shaping the domain model
[TODO]
**Sources:** [TODO]
