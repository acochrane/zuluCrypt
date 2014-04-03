
/*
 *
 *  Copyright (c) 2014
 *  name : mhogo mchungu
 *  email: mhogomchungu@gmail.com
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QProcess>
#include <QByteArray>
#include <QString>
#include <QObject>
#include <QFile>

auto gpg = []( const QString& e,const QString& keyFile,const QString& password ){

	QString exe ;
	if( e.isEmpty() ){
		exe = QString( "/usr/local/bin/gpg" ) ;
		if( !QFile::exists( exe ) ){
			exe = QString( "/usr/bin/gpg" ) ;
			if( !QFile::exists( exe ) ){
				/*
				 * failed to find gpg binary,return with a misleading error for now
				 */
				return QByteArray() ;
			}
		}
	}else{
		exe = e ;
	}

	QString arg ;
	if( password.isEmpty() ){
		arg = QString( "%1 --no-tty --yes --no-mdc-warning --no-verbose -d %2" ).arg( exe ).arg( keyFile ) ;
	}else{
		arg = QString( "%1 --no-tty --yes --no-mdc-warning --no-verbose --passphrase-fd 0 -d  %2" ).arg( exe ).arg( keyFile ) ;
	}

	QProcess p ;

	p.start( arg ) ;

	p.waitForStarted() ;

	p.write( password.toLatin1() ) ;
	p.closeWriteChannel() ;
	p.waitForFinished( -1 ) ;
	return p.readAllStandardOutput() ;
} ;