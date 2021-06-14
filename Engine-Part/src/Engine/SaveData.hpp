#ifndef _SAVE_DATA_H_
#define _SAVE_DATA_H_

/// Управление данными для сохранеия
namespace Data {
    /// Структура контейнера данных
    struct DataContainer {
        long countTurn;
        long currentPosition;
        bool b_direction;
        bool b_canMove;
        bool b_mode;
    };

    /// Контейнер данных
    DataContainer dataContainer = { 0, 0, true, false, true };

    /// Сохранить данные
    void Save() {
        eeprom_write_block((void*)&dataContainer, 10, sizeof(dataContainer));
    }

    /// Загрузить данные
    void Load() {
        eeprom_read_block((void*)&dataContainer, 10, sizeof(dataContainer));
        Serial.print("[DEBUG] CountTurn: ");
        Serial.println(dataContainer.countTurn);
    }
};

#endif