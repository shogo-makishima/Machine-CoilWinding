#ifndef _SAVE_DATA_H_
#define _SAVE_DATA_H_

/// Управление данными для сохранеия
namespace Data {
    /// Инициализирован ли экран
    bool b_isInit = false;
    /// Инициализирован ли экран
    bool b_isBlock = false;

    /// Структура контейнера данных
    struct DataContainer {
        double countTurn;
        long currentPosition;
        double limit_countTurn;
        bool b_direction;
        bool b_canMove;
        bool b_mode;
        bool b_mainDirection;
        int speed;
    };

    /// Контейнер данных
    DataContainer dataContainer = { 0.0f, 0, 5.0f, true, false, true, true, 1000 };

    /// Контейнер стандартных значений
    DataContainer defaultData = { 0.0f, 0, 10.5f, true, false, true, true, 1000 };

    /// Сохранить данные
    void Save() {
        eeprom_write_block((void*)&dataContainer, 10, sizeof(dataContainer));
    }

    /// Загрузить данные
    void Load() {
        eeprom_read_block((void*)&dataContainer, 10, sizeof(dataContainer));
    }

    /// Сбросить настройки
    void Clear() {
        for (int i = 0; i < EEPROM.length(); i++) EEPROM.update(i, 0);

        dataContainer.countTurn = defaultData.countTurn;
        dataContainer.currentPosition = defaultData.currentPosition;
        dataContainer.limit_countTurn = defaultData.limit_countTurn;
        dataContainer.b_direction = defaultData.b_direction;
        dataContainer.b_canMove = defaultData.b_canMove;
        dataContainer.b_mode = defaultData.b_mode;
        dataContainer.b_mainDirection = defaultData.b_mainDirection;
        dataContainer.speed = defaultData.speed;
    }
};

#endif