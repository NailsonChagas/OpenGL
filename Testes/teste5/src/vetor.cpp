#include <iostream>
#include "vetor.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

void constructors(){
    //gerando vetores de pontos flutuantes
    glm::vec4 Point2{10.0f, 10.0f, 0.0f, 0.0f};
    glm::vec3 Point1{10.0f, 0.0f, 0.0f};
    glm::vec2 Point0{10.0f, 10.0f};

    //gerando vetor de inteiro
    glm::ivec2 Point3{3, 4};

    //gerando vetor de booleanos
    glm::bvec3 Point4{false, true, false};

    //gerando vetores de double float
    glm::dvec2 Point5{10.0, 10.0};

    //teste
    glm::vec3 Point6{Point0, 1.0f};
    
    std::cout << std::endl;
    std::cout << "Point 0: " << glm::to_string(Point0) << std::endl; 
    std::cout << "Point 1: " << glm::to_string(Point1) << std::endl;
    std::cout << "Point 2: " << glm::to_string(Point2) << std::endl;
    std::cout << "Point 3: " << glm::to_string(Point3) << std::endl;
    std::cout << "Point 4: " << glm::to_string(Point4) << std::endl;
    std::cout << "Point 5: " << glm::to_string(Point5) << std::endl;
    std::cout << "Point 6: " << glm::to_string(Point6) << std::endl;
}

void components(){
    glm::vec3 P{1, 2, 3};
    
    std::cout << std::endl;
    std::cout << "X: " << P.x << " Y: " << P.y << " Z: " << P.z << std::endl;
    std::cout << "R: " << P.r << " G: " << P.g << " B: " << P.b << std::endl; 
    std::cout << "0: " << P[0] << " 1: " << P[1] << " 2: " << P[2] << std::endl; 
}

void operations(){
    glm::vec3 P0{10.0f, 10.0f, 0.0f};
    glm::vec3 P1{10.0f, 10.0f, 10.0f};

    glm::vec3 resultado;

    std::cout << std::endl;
    
    //soma
    resultado = P0 + P1;
    std::cout << "Soma: " << glm::to_string(resultado) << std::endl;

    //multiplicar por um escalar
    resultado = 5.0f * P0;
    std::cout << "Mult. Escalar: " << glm::to_string(resultado) << std::endl;

    //multiplicar as coordenadas de um vetor pelas de outro vetor
    resultado = P0 * P1;
    std::cout << "Mult. Vetorial: " << glm::to_string(resultado) << std::endl;

    //módulo de um vetor
    float comprimentoVetor = glm::length(P1);
    std::cout << "Comprimento vetor: " << comprimentoVetor << std::endl;

    //Normalizar um vetor
    glm::vec3 norm;

    norm  = glm::normalize(P0);
    std::cout << "Vetor normal: " << glm::to_string(norm)<< std::endl;

    //produto escalar (dot product)
    float dot = glm::dot(P0, P1);
    std::cout << "Produto escalar: " << dot << std::endl;

    //produto vetorial (cross product)
    glm::vec3 produto;
    
    produto = glm::cross(P0, P1); 
    std::cout << "Produto vetorial: " << glm::to_string(produto) << std::endl;

    //distancia entre dois pontos
    float distance = glm::distance(P0, P1);
    std::cout << "Distancia:  " << distance << std::endl;

    //calculo do vetro de refração
    glm::vec3 Refract = glm::refract(P0, norm, 1.0f);
    std::cout << "Refract: " << glm::to_string(Refract) << std::endl;

    //calculo do vetor de reflexão
    glm::vec3 Reflect = glm::reflect(P0, norm);
    std::cout << "Reflect: " << glm::to_string(Reflect) << std::endl;

}