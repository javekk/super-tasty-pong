
#include "ParticleGenerator.hpp"


ParticleGenerator::ParticleGenerator(
    Shader shader
    , Texture texture
    , unsigned int amount
) : 
    shader(shader)
    , texture(texture)
    , amount(amount) {
    this->init();
}

void ParticleGenerator::init() {
    unsigned int VBO;
    float vertices[] = {
        // position     // texture
        0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 0.0f,
        0.0f, 0.0f,     0.0f, 0.0f,

        0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 1.0f,     1.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 0.0f
    }; 
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);

    for (unsigned int i = 0; i < this->amount; ++i)
        this->particles.push_back(Particle());
}


void ParticleGenerator::update(
    float deltatime
    , GameObject &object
    , unsigned int newParticles
    , glm::vec2 offset
){
    for (unsigned int i = 0; i < newParticles; ++i){
        int unusedParticle = this->firstUnusedParticle();
        this->respawnParticle(this->particles[unusedParticle], object, offset);
    }
    for (unsigned int i = 0; i < this->amount; ++i){
        Particle &p = this->particles[i];
        p.life -= (deltatime * 3); 
        if (p.life > 0.0f) { 
            p.position -= p.velocity * deltatime; 
            p.color.a -= deltatime * 2.5f;
        }
    }
}

void ParticleGenerator::draw(){
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); //glow effect
    this->shader.use();
    for (Particle particle : this->particles){
        if (particle.life > 0.0f){
            this->shader.setVector2f("offset", particle.position);
            this->shader.setVector4f("color", particle.color);
            this->texture.bind();
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

unsigned int ParticleGenerator::firstUnusedParticle(){
    // try from the latest
    for (unsigned int i = this->lastUsedParticleIndex; i < this->amount; ++i){
        if (this->particles[i].life <= 0.0f){
            this->lastUsedParticleIndex = i;
            return this->lastUsedParticleIndex;
        }
    }
    // check before it
    for (unsigned int i = 0; i < lastUsedParticleIndex; ++i){
        if (this->particles[i].life <= 0.0f){
            this->lastUsedParticleIndex = i;
            return this->lastUsedParticleIndex;
        }
    }
    // re-use the first one
    this->lastUsedParticleIndex = 0; 
    return this->lastUsedParticleIndex;
}

void ParticleGenerator::respawnParticle(
    Particle &particle
    , GameObject &object
    , glm::vec2 offset
){
    float random = ((rand() % 100) - 50) / 10.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f); // random brightness
    particle.position = object.position + random + offset; // random positions
    particle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
    particle.life = 1.0f;
    particle.velocity = object.velocity * 0.1f;
}

