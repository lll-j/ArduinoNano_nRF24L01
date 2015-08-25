/*
nRF24L01 Arduino Receiver���ն�

Ansifa
2015/3/7

���Žӷ���
nRF24L01   Arduino UNO
VCC <-> 3.3V
GND <-> GND
CE  <-> D9
CSN <-> D10
MOSI<-> D11
MISO<-> D12
SCK <-> D13
IRQ <-> ����
*/

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

    //����һ������adata�洢���ս��,oldadata�洢�ɽ������ֹ��ͬ���ˢ����
    unsigned int adata = 0, oldadata = 0;

void setup()
{
    Serial.begin(9600);

    //---------��ʼ�����֣�������ʱ�޸�---------
    Mirf.cePin = 9;     //����CE����ΪD9
    Mirf.csnPin = 10;   //����CE����ΪD10
    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();  //��ʼ��nRF24L01

    //---------���ò��֣�������ʱ�޸�---------
    //���ý��ձ�ʶ��"Rev01"
    Mirf.setRADDR((byte *)"Rec01");
    //����һ���շ����ֽ��������﷢һ��������
    //дsizeof(unsigned int)��ʵ�ʵ���2�ֽ�
    Mirf.payload = sizeof(unsigned int);
    //����ͨ����������0~128���շ�����һ�¡�
    Mirf.channel = 3;
    Mirf.config();

    //ע��һ��ArduinoдSender.ino����һ��дReceiver.ino��
    //�����������д����Receiver.ino����
    Serial.println("I'm Receiver...");
}

void loop()
{
    //����һ���ݴ����飬��СΪMirf.payload��
    byte data[Mirf.payload];
    if(Mirf.dataReady())    //�ȴ���������׼����
    {
        Mirf.getData(data);    //�������ݵ�data����
        //data[1]<����8λ��data[0]�����������ݡ�
        adata = (unsigned int)((data[1] << 8) | data[0]);

        //����һ�ν���Ƚϣ�������ͬ���ˢ��,���ʹ�������
        if(adata != oldadata)
        {
            oldadata = adata; //���ν����Ϊ��ʷ�����
            //Serial.print�������
            Serial.print("A0=");
            Serial.println(adata);
            //Ҳ�������˫�ֽ�����
            //Serial.write(data[1]);
            //Serial.write(data[0]);
        }

    }
}
