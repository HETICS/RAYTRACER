# Domain model

How the ray tracer sees the client's problem, at the end of week 1 (m1).

The camera sends one ray through each pixel of the image. The scene finds the nearest surface the ray hits. That surface's material, lit by the scene's light, gives the pixel its colour. A saver writes the image to a file.

```mermaid
classDiagram
    direction LR

    class Vector {
        x, y, z
        +, -, t * v
        dot(other)
        length()
        normalised()
    }

    class Ray {
        origin: Vector
        direction: Vector
        at(t) Vector
    }

    class Camera {
        position: Vector
        screenWidth
        rayThroughPixel(x, y, width, height) Ray
        render(scene, width, height) Image
    }

    class Scene {
        light: Light
        add(shape)
        nearestHit(ray) HitInfo?
    }

    class Shape {
        <<interface>>
        hit(ray) HitInfo?
    }
    class Sphere {
        center: Vector
        radius
    }
    class Plane {
        point: Vector
        normal: Vector
    }

    class HitInfo {
        t
        point: Vector
        normal: Vector
        material
    }

    class Material {
        <<interface>>
        shade(hit, light) Colour
    }
    class FlatShader {
        colour: Colour
    }
    class LambertShader {
        colour: Colour
    }

    class Light {
        position: Vector
        colour: Colour
    }

    class Colour {
        r, g, b
    }

    class Image {
        width, height
        pixel(x, y) Colour
        setPixel(x, y, colour)
    }

    class ImageSaver {
        <<interface>>
        save(image, path)
    }
    class PngSaver

    Camera "1" --> "*" Ray : sends one per pixel
    Camera ..> Scene : traces rays in
    Camera ..> Image : fills
    Scene "1" *-- "1" Light : lit by
    Scene "1" *-- "*" Shape : holds
    Shape <|.. Sphere
    Shape <|.. Plane
    Shape ..> HitInfo : gives the nearest
    Sphere "*" o-- "1" Material : has a
    Plane "*" o-- "1" Material : has a
    HitInfo --> Material : of the surface hit
    Material <|.. FlatShader
    Material <|.. LambertShader
    Material ..> Colour : gives
    Image "1" *-- "*" Colour : one per pixel
    ImageSaver <|.. PngSaver
    ImageSaver ..> Image : saves
```

## Words we use

| Word | Meaning in the code |
|---|---|
| Ray | A half line from an origin, in a direction: the point at t is `origin + t * direction` |
| Hit | Where a ray meets a surface: `t`, the point, the unit normal there, and the surface's material |
| Normal | The unit vector perpendicular to the surface at the hit point, pointing outwards |
| Material | How a surface turns light into a colour (flat, or Lambert's law) |
| Screen | A rectangle 1 in front of the camera, `screenWidth` wide, cut into the image's pixels |
| Coordinates | x to the right, y up, z forward; pixels counted from the top left corner |

## Who does what

- `trace(ray, scene)` colours one pixel: the nearest hit's material shades it with the scene's light, or the pixel is black.
- A shape **has a** material; it is not a kind of material. The same material can be shared by several shapes.
- The scene owns its shapes. A hit only points to the material, which lives as long as its shape.
