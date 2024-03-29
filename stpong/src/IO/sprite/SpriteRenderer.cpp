
#include "SpriteRenderer.hpp"


SpriteRenderer::SpriteRenderer(Shader &shader){
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer(){
    glDeleteVertexArrays(1, &this->VAO);
}

void SpriteRenderer::initRenderData(){
    
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
}


void SpriteRenderer::drawSprite(
    Texture &texture
    , glm::vec2 position
    , float rotate
    , glm::vec2 size
    , glm::vec3 color
) {

    this->shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f)); 
  
    this->shader.setMatrix4("model", model);
    this->shader.setVector3f("spriteColor", color);
  
    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}  