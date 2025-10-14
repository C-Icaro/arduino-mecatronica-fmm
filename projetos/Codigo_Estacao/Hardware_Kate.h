
#define uKate 1
#define Kate3 2
#define Kate4 3


#define estacao uKate
//#define estacao Kate3
//#define estacao Kate4

#if estacao == uKate
/**
 * @brief Pino que alimenta especificamente o sensor EC-5
 */
    #define VCC_EC5 27
    /**
     * @brief Pino que alimenta todos os sensores da estação
     *
     * Trabalho conjunto com INITIALIZE_PIN_2
     */
    #define INITIALIZE_PIN_1 18
    /**
     * @brief Pino que alimenta todos os sensores da estação
     *
     * Trabalho conjunto com INITIALIZE_PIN_1
     */
    #define INITIALIZE_PIN_2 5
    /**
     * @brief Pino que ativa o Led de cor vermelha
     * embutido na placa da estação
     */
    #define RED_LED 17
    /**
     * @brief Pino que ativa o Led de cor amarela
     * embutido na placa da estação
     */
    #define YELLOW_LED 16 //2
    /**
     * @brief Pino que ativa o Led de cor verde
     * embutido na placa da estação
     */
    #define GREEN_LED 4
    /**
     * @brief Pino que está ligado o botão que ativa o debug
     */
    // Para UKate: 14
    // Para Kate: 23
    #define DEBUG_PIN 14
    /**
     * @brief Pino que está ligado ao pluviômetro
     */
    #define PLUVIOMETER_PIN 35

    #define DS18B20_PIN 19
    #define ANEM_PIN 19
    #define BATERIA_PIN 36

#elif estacao == Kate3
    /**
     * @brief Pino que alimenta especificamente o sensor EC-5
     */
    #define VCC_EC5 27
    /**
     * @brief Pino que alimenta todos os sensores da estação
     *
     * Trabalho conjunto com INITIALIZE_PIN_2
     */
    #define INITIALIZE_PIN_1 18
    /**
     * @brief Pino que alimenta todos os sensores da estação
     *
     * Trabalho conjunto com INITIALIZE_PIN_1
     */
    #define INITIALIZE_PIN_2 5
    /**
     * @brief Pino que ativa o Led de cor vermelha
     * embutido na placa da estação
     */
    #define RED_LED 17
    /**
     * @brief Pino que ativa o Led de cor amarela
     * embutido na placa da estação
     */
    #define YELLOW_LED 16 //2
    /**
     * @brief Pino que ativa o Led de cor verde
     * embutido na placa da estação
     */
    #define GREEN_LED 4
    /**
     * @brief Pino que está ligado o botão que ativa o debug
     */
    // Para UKate: 14
    // Para Kate: 23
    #define DEBUG_PIN 23
    /**
     * @brief Pino que está ligado ao pluviômetro
     */
    #define PLUVIOMETER_PIN 35

    #define DS18B20_PIN 19
    #define ANEM_PIN 19
    #define BATERIA_PIN 36

#elif estacao == Kate4

        /**
     * @brief Pino que alimenta especificamente o sensor EC-5
     */
    #define VCC_EC5 27
    /**
     * @brief Pino que alimenta todos os sensores da estação
     *
     * Trabalho conjunto com INITIALIZE_PIN_2
     */
    #define INITIALIZE_PIN_1 34
    /**
     * @brief Pino que alimenta todos os sensores da estação
     *
     * Trabalho conjunto com INITIALIZE_PIN_1
     */
    #define INITIALIZE_PIN_2 34
    /**
     * @brief Pino que ativa o Led de cor vermelha
     * embutido na placa da estação
     */
    #define RED_LED 18
    /**
     * @brief Pino que ativa o Led de cor amarela
     * embutido na placa da estação
     */
    #define YELLOW_LED 5 //2
    /**
     * @brief Pino que ativa o Led de cor verde
     * embutido na placa da estação
     */
    #define GREEN_LED 4
    /**
     * @brief Pino que está ligado o botão que ativa o debug
     */
    // Para UKate: 14
    // Para Kate: 23
    #define DEBUG_PIN 23
    /**
     * @brief Pino que está ligado ao pluviômetro
     */
    #define PLUVIOMETER_PIN 35

    #define DS18B20_PIN 19
    #define ANEM_PIN 19
    #define BATERIA_PIN 36


#endif