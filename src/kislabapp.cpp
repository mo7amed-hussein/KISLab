#include "kislabapp.h"

KISLabApp::KISLabApp(int &argc, char *argv[]) : QApplication(argc,argv)
{

}

bool KISLabApp::event( QEvent * pEvent )
{
    if ( pEvent->type() == QEvent::ApplicationActivate )
        qDebug() << "ApplicationActivate";
    else if ( pEvent->type() == QEvent::ApplicationDeactivate )
        qDebug() << "ApplicationDeactivate";
    else if(pEvent->type() == QEvent::Clipboard)
        qDebug() << "clipboard";
    return QApplication::event( pEvent );
}
