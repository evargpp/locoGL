#version 330 core
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;    // pozycja latarni
uniform vec3 lightColor;  // kolor �wiat�a
uniform vec3 objectColor; // kolor obiektu
uniform vec3 viewPos;     // pozycja kamery (dla specular je�li chcesz)
uniform float uLightIntensity;

void main() {
    // Normale i kierunki
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // Diffuse (tylko jedno �wiat�o)
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Mo�esz da� ambient jako 0, �eby ca�kowicie wy��czy� inne �r�d�a
    vec3 ambient = vec3(0.0);

    // ��czny kolor
    vec3 result = (ambient + diffuse) * objectColor;
//    FragColor = vec4(result, 1.0);

    vec3 lightColor = vec3(1.0, 1.0, 0.8); // np. ciep�e �wiat�o
    vec3 finalColor = lightColor * uLightIntensity * result;
    
    // reszta fragment shadera
    FragColor = vec4(finalColor, 1.0);
}