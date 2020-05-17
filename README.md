# ЗАДАНИЕ
1. Реализовать устройство управления 7-сегментными индикаторами (не менее 2-х). Устройство должно подсчитывать количество нажатий на кнопку и отображать его с помощью 7-сегментных индикаторов по следующему принципу:
  - кратковременное нажатие на кнопку увеличивает значение счетчика на единицу;
  -	долговременное нажатие на кнопку (более 3 секунд) приводит к приращению счетчика на единицу каждую секунду;
  -	при выходе за пределы счета, заданного константным значением в отдельной переменной, загорается индикатор-светодиод «переполнение» (должен гаснуть после следующего изменения счетчика), а для счетчика устанавливается нулевое значение;
  - для сброса значения счетчика до нуля должна быть реализована отдельная кнопка.
2. Выполнить симуляцию работы программы в среде Proteus

![Image of project](../images/Picture1.png?raw=true)
