class Shell : public QWidget {
Q_OBJECT
private:
    QProcess*  m_process;
    QLineEdit* m_ptxtCommand;
    QTextEdit* m_ptxtDisplay;

public:
    Shell(QWidget* pwgt = 0) : QWidget(pwgt)
    {
        m_process     = new QProcess(this);
        m_ptxtDisplay = new QTextEdit;

        QLabel* plbl = new QLabel("&Command:");

        m_ptxtCommand = new QLineEdit("dir");
        plbl->setBuddy(m_ptxtCommand);

        QPushButton* pcmd = new QPushButton("&Enter");

        connect(m_process,
                SIGNAL(readyReadStandardOutput()),
                SLOT(slotDataOnStdout())
               );
        connect(m_ptxtCommand,
                SIGNAL(returnPressed()),
                SLOT(slotReturnPressed())
               );
        connect(pcmd, SIGNAL(clicked()), SLOT(slotReturnPressed()));

        //Layout setup
        QHBoxLayout* phbxLayout = new QHBoxLayout;
        phbxLayout->addWidget(plbl);
        phbxLayout->addWidget(m_ptxtCommand);
        phbxLayout->addWidget(pcmd);

        QVBoxLayout* pvbxLayout = new QVBoxLayout;
        pvbxLayout->addWidget(m_ptxtDisplay);
        pvbxLayout->addLayout(phbxLayout);
        setLayout(pvbxLayout);
    }

public slots:
    void slotDataOnStdout()
    {
        m_ptxtDisplay->append(m_process->readAllStandardOutput());
    }

    void slotReturnPressed()
    {
        QString strCommand = "";
#ifdef Q_WS_WIN
        strCommand = "cmd /C ";
#endif
        strCommand += m_ptxtCommand->text();
        m_process->start(strCommand);
    }
};
/*
В конструкторе класса Shell производится создание объекта класса QProgress.
Его сигнал readyReadStandardOutput() соединяется со слотом slotDataOnStdout(),
в котором вызывается метод readAllstandardOutput() для считывания всего содержимого стандартного потока.
После считывания эти данные добавляются, вызовом метода append(), в виджет многострочного текстового поля m_ptxtDisplay.

Слот slotReturnPressed() соединен с сигналом
кнопки clicked() (указатель pcmd) и с сигналом однострочного текстового поля returnPressed() (указатель m_txtCommand).
Некоторые команды ОС Windows, например — dir, не являются отдельными программами,
поэтому они должны быть исполнены посредством командного интерпретатора cmd.
Поэтому для ОС Windows в командную строку сначала добавляется строка "cmd /С".
Во всех остальных, введенная в однострочном текстовом поле строка передается как есть, без дополнений.
Для запуска процесса вызывается метод start().
*/
