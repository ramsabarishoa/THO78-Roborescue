#include "atvwindow.h"
#include "ui_atvwindow.h"

ATVWindow::ATVWindow(ATV & atv, QWidget *parent) :
    QMainWindow(parent),
    atv(atv),
    ui(new Ui::ATVWindow)
{
    ui->setupUi(this);

    connect(ui->abortButton   , SIGNAL(clicked()), this, SLOT(handleButton()));
    connect(ui->armButton     , SIGNAL(clicked()), this, SLOT(handleButton()));
    connect(ui->shutdownButton, SIGNAL(clicked()), this, SLOT(handleButton()));

    connect(ui->steeringScrollBar, SIGNAL(valueChanged(int)), this, SLOT(scrollbarValueChanged(int)));

    connect(&timer, SIGNAL(timeout()), this, SLOT(timerTick()));
    timer.start(1000);
}

ATVWindow::~ATVWindow() {
    delete ui;
}

void ATVWindow::handleButton(){
   QPushButton * button = static_cast<QPushButton *>(sender());
   if(button == nullptr) return;

   if(button == ui->abortButton){
      if(!ui->abortButton->isEnabled()) return;
      //atv.emergencyStop();
      armed(false);
   }else if(button == ui->armButton){
      if(ui->armButton->text() == "Arm"){
         //atv.arm();
         armed(true);
      }else{
         //atv.disarm();
         armed(false);
      }
   }else if(button == ui->shutdownButton){
      if(!ui->shutdownButton->isEnabled()) return;
      atv.shutdown();
      armed(false);
   }
}

void ATVWindow::scrollbarValueChanged(int value){
   ui->steeringScrollBar->setValue(atv.getSteeringDirection());
}

void ATVWindow::timerTick(){
   //ui->batteryStatusBar->setValue(static_cast<int>(atv.batteryStatus()));
   ui->speedLCD->display(atv.getGroundSpeed());
}

void ATVWindow::armed(bool is_armed){
   ui->armButton->setText(is_armed ? "Disarm" : "Arm");
   ui->abortButton->setEnabled(is_armed);
   ui->shutdownButton->setEnabled(is_armed);
   ui->steeringScrollBar->setEnabled(is_armed);

}
