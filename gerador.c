#include "stdio.h"
#include "stdlib.h"
#include "time.h"


typedef struct {
    int hora, min, seg;
} t_time_stamp;

t_time_stamp timestamp() {
  // Get the current time in seconds since the epoch (Jan 1, 1970)
  time_t current_time = time(NULL);

  // Convert the time to a human-readable format using local time zone
  struct tm *local_time = localtime(&current_time);

  // Access individual time components (e.g., hour, minute, second)
  int hour = (local_time->tm_hour + rand()) % 24;
  int minute = (local_time->tm_min + rand()) % 60;
  int second = (local_time->tm_sec + rand()) % 60;

  return (t_time_stamp){.hora=hour, .min = minute, .seg =second};
}


int sensor(int nro_sensores){
    //srand(time(NULL));
    return (1 + (rand()%nro_sensores));
}

#define MIN_TEMP -10 // Minimum measurable temperature (°C)
#define MAX_TEMP 50 // Maximum measurable temperature (°C)

double temperatura(float baseTemp, float ambientTemp) {
  // Simulate heat transfer between sensor and environment
  float temperatureChange = 0.1 * (ambientTemp - baseTemp); // Adjust coefficient for desired thermal response

  // Introduce random noise to mimic sensor imperfections
  //srand(time(NULL));
  float noise = (float)rand() / RAND_MAX * 0.5; // Random noise between -0.25 and 0.25 °C
  temperatureChange += noise;

  // Update base temperature considering heat transfer and noise
  float newTemp = baseTemp + temperatureChange;

  // Ensure value stays within the measurable range
  newTemp = (newTemp < MIN_TEMP) ? MIN_TEMP : newTemp;
  newTemp = (newTemp > MAX_TEMP) ? MAX_TEMP : newTemp;

  return newTemp;
}



#define SENSOR_RANGE 5 // Detection range in meters (adjust as needed)

int movimento(int short_duration, int long_duration){

    //srand(time(NULL));
    int movement = rand() % 10; // Generate random number between 0 and 9

    if (movement < 3){ // Movement detected if random number is less than 3 (adjust probability as needed)
        return rand()%long_duration;
    }else{
        return rand()%short_duration;
    }
}

#define MIN_LUMEN 0 // Minimum measurable lumen value
#define MAX_LUMEN 1000 // Maximum measurable lumen value

int luminosidade(int ambientLight) {
  // Simulate external light affecting sensor readings
  int baseValue = ambientLight * (rand() % 50); // Adjust multiplier for desired sensitivity

  // Introduce random noise to mimic sensor imperfections
  //srand(time(NULL));
  int noise = rand() % 10; // Generate random noise between -5 and 4 lumens
  baseValue += noise;

  // Ensure value stays within the measurable range
  baseValue = (baseValue < MIN_LUMEN) ? MIN_LUMEN : baseValue;
  baseValue = (baseValue > MAX_LUMEN) ? MAX_LUMEN : baseValue;

  return baseValue;
}


#define MIN_HUMIDITY 0 // Minimum measurable humidity percentage (%)
#define MAX_HUMIDITY 100 // Maximum measurable humidity percentage (%)

int umidade(int baseHumidity, int ambientTemp) {
  // Simulate humidity change based on ambient temperature
  int humidityChange = (ambientTemp - 20) * 2; // Adjust coefficient for desired sensitivity

  // Introduce random noise to mimic sensor imperfections
  //srand(time(NULL));
  int noise = rand() % 5; // Random noise between -2 and 2 percentage points

  // Update base humidity considering ambient temperature and noise
  int newHumidity = baseHumidity + humidityChange + noise;

  // Ensure value stays within the measurable range
  newHumidity = (newHumidity < MIN_HUMIDITY) ? MIN_HUMIDITY : newHumidity;
  newHumidity = (newHumidity > MAX_HUMIDITY) ? MAX_HUMIDITY : newHumidity;

  return newHumidity;
}




int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int samples;

    scanf("%d", &samples);
    for (int i=1;i<=samples;i++){
        int t_sensor = sensor(4);
        t_time_stamp t = timestamp();
        if (t_sensor == 1){ //temperatura
            double temp = temperatura(17, 50);
            printf("%d %.3lf %02d:%02d:%02d\n", t_sensor, temp, t.hora, t.min, t.seg ); 
        }else if (t_sensor == 2){ // luminosidade
            int lumen = luminosidade(10);
            printf("%d %d %02d:%02d:%02d\n", t_sensor, lumen, t.hora, t.min, t.seg ); 
                
        }else  if(t_sensor == 3){ // movimento
            int duracao = movimento(1000, 1000*60);
             printf("%d %d %02d:%02d:%02d\n", t_sensor, duracao, t.hora, t.min, t.seg ); 
        }else { // umidade
             int umid = umidade(75, 40); 
             printf("%d %d %02d:%02d:%02d\n", t_sensor, umid, t.hora, t.min, t.seg ); 

        }

    }   

    /* code */
    return 0;
}