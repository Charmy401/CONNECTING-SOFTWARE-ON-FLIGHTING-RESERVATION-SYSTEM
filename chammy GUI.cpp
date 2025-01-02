#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

class FlightReservationWindow : public QWidget {
public:
    FlightReservationWindow(QWidget *parent = nullptr);

private slots:
    void viewFlights();
    void makeReservation();

private:
    QLabel *label;
};

FlightReservationWindow::FlightReservationWindow(QWidget *parent)
    : QWidget(parent), label(new QLabel(this)) {

    // Set window title and layout
    setWindowTitle("Flight Reservation System");
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add label to show status
    label->setText("Welcome to the Flight Reservation System");
    layout->addWidget(label);

    // Create View Flights button
    QPushButton *viewFlightsButton = new QPushButton("View Available Flights", this);
    layout->addWidget(viewFlightsButton);
    connect(viewFlightsButton, &QPushButton::clicked, this, &FlightReservationWindow::viewFlights);

    // Create Make Reservation button
    QPushButton *makeReservationButton = new QPushButton("Make a Reservation", this);
    layout->addWidget(makeReservationButton);
    connect(makeReservationButton, &QPushButton::clicked, this, &FlightReservationWindow::makeReservation);

    // Set the layout
    setLayout(layout);
}

void FlightReservationWindow::viewFlights() {
    QMessageBox::information(this, "Available Flights", "Here are the available flights:\n1. Delta Airlines\n2. American Airlines\n3. United Airlines");
}

void FlightReservationWindow::makeReservation() {
    QMessageBox::information(this, "Make a Reservation", "You can now reserve a flight.\nPlease enter your details in the next steps.");
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FlightReservationWindow window;
    window.show();

    return app.exec();
}
