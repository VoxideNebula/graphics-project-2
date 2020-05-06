#ifndef _CSCI441_RENDERER_H_
#define _CSCI441_RENDERER_H_

#include "camera.h"
#include "hit.h"
#include "light.h"
#include "ray.h"
#include "intersector.h"

class Renderer {

    Intersector* _intersector;

    int clamp255(float v) {
        return std::max(0.0f, std::min(255.0f, 255.0f*v));
    }


    rgb_t to_color(const glm::vec3 c) {
        return make_colour(clamp255(c.x), clamp255(c.y), clamp255(c.z));
    }


    glm::vec3 phong(const Hit& hit, const Light* light, const glm::vec3& eye) {

        float ambientStrength = 0.2;
        float specularStrength = 0.5;
        float shinyness = 2;

        glm::vec3 pos = hit.position();
        glm::vec3 normal = hit.normal();

        glm::vec3 light_dir = glm::normalize(light->direction(pos));

        float ambient = ambientStrength;

        float diffuse = glm::max(glm::dot(normal, light_dir), 0.0f);

        glm::vec3 view_dir = glm::normalize(eye - pos);
        glm::vec3 reflectDir = glm::reflect(-light_dir, normal);
        float specular = specularStrength *
            pow(std::fmax(glm::dot(view_dir, reflectDir), 0.0), shinyness);

        glm::vec3 light_color  =
            (ambient+diffuse+specular)
            * light->attenuation(pos)
            * light->color();

        return light_color*hit.color();
    }


    glm::vec3 shade(const glm::vec3 backgroundColor, const glm::vec3 pos, const Lights& lights, const Hit& hit) {
        glm::vec3 color = backgroundColor;
        if (hit.is_intersection()) {
            color = glm::vec3(0,0,0);
            for (auto light : lights)
            {
                //phong shading
                color += phong(hit, light, pos);
                
                

            }
        
            
        }

        
        return color;
    }

    glm::vec3 reflect(const Camera& camera, const Lights& lights, const Hit& hit, const Ray& ray, const World& world)
    {
        //create ray reflected off surface on other side of surface normal
        if (hit.is_intersection())
        {
            glm::vec3 normal = hit.normal();
            Ray reflectedRay;
            reflectedRay.origin = hit.position();
            reflectedRay.direction = ray.direction - (2.0f * (glm::dot(normal, ray.direction) * normal));
            reflectedRay.origin += 0.001f * reflectedRay.direction;
            Hit newHit = _intersector->find_first_intersection(world, reflectedRay);
            if (newHit.is_intersection()){return shade(glm::vec3(0,0,0), reflectedRay.origin, lights, newHit);}else{return glm::vec3(0,0,0);}
        } else {return glm::vec3(0,0,0);}
    }
        

    glm::vec3 render_pixel(
        const Camera& camera,
        const Lights& lights,
        const World& world,
        const Ray& ray
    ) {

        Hit hit = _intersector->find_first_intersection(world, ray);
        return shade(camera.background, camera.pos, lights, hit) + 0.8f * reflect(camera, lights, hit, ray, world);
    }

public:

    Renderer(Intersector* intersector) : _intersector(intersector) { }

    void render(
        bitmap_image &image,
        const Camera& camera,
        const Lights& lights,
        const World& world
    ) {
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                Ray ray = camera.make_ray(image.width(), image.height(), x, y);
                glm::vec3 c = render_pixel(camera, lights, world, ray);
                image.set_pixel(x, image.height()-y-1, to_color(c));
            }
        }
    }
};

#endif
