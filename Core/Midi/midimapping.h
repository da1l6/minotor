/*
 * Copyright 2012, 2013 Gauthier Legrand
 * Copyright 2012, 2013 Romuald Conty
 * 
 * This file is part of Minotor.
 * 
 * Minotor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Minotor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Minotor.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIDIMAPPING_H
#define MIDIMAPPING_H

#include <QObject>
#include <QMap>
#include <QVariant>

class MidiMapping : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString vendor READ vendor WRITE setVendor STORED true)
    Q_PROPERTY(QString product READ product WRITE setProduct STORED true)
    Q_PROPERTY(QString comment READ comment WRITE setComment STORED true)
    Q_PROPERTY(int tracks READ tracks WRITE setTracks STORED true)
    Q_PROPERTY(int knobsPerTrack READ knobsPerTrack WRITE setKnobsPerTrack STORED true)
    Q_PROPERTY(int triggersPerTrack READ triggersPerTrack WRITE setTriggersPerTrack STORED true)
    Q_PROPERTY(QMap map READ map WRITE setMap STORED true)
    Q_PROPERTY(bool acceptClock READ acceptClock WRITE setAcceptClock STORED true)
    Q_PROPERTY(bool acceptProgramChange READ acceptProgramChange WRITE setAcceptProgramChange STORED true)
    Q_PROPERTY(bool acceptControlChange READ acceptControlChange WRITE setAcceptControlChange STORED true)
    Q_PROPERTY(bool acceptNoteChange READ acceptNoteChange WRITE setAcceptNoteChange STORED true)

public:
    explicit MidiMapping(QObject *parent = 0);
    
    void setVendor(const QString& vendor);
    QString vendor() const { return _vendor; }

    void setProduct(const QString& product);
    QString product() const { return _product; }

    void setComment(const QString& comment);
    QString comment() const { return _comment; }

    void setTracks(const int tracks);
    int tracks() const { return _tracks; }

    void setKnobsPerTrack(const int knobsPerTrack);
    int knobsPerTrack() const { return _knobsPerTrack; }

    void setTriggersPerTrack(const int triggersPerTrack);
    int triggersPerTrack() const { return _triggersPerTrack; }

    void setAcceptClock(const bool& acceptClock) { _acceptClock = acceptClock; }
    bool acceptClock() { return _acceptClock; }

    void setAcceptProgramChange(const bool& acceptProgramChange) { _acceptProgramChange = acceptProgramChange; }
    bool acceptProgramChange() { return _acceptProgramChange; }

    void setAcceptControlChange(const bool& acceptControlChange) { _acceptControlChange = acceptControlChange; }
    bool acceptControlChange() { return _acceptControlChange; }

    void setAcceptNoteChange(const bool& acceptNoteChange) { _acceptNoteChange = acceptNoteChange; }
    bool acceptNoteChange() { return _acceptNoteChange; }

    void setMap(QMap<QString,QVariant> map) { _map = map; }
    QMap<QString,QVariant> map() const { return _map; }

    void addAssignedMidiControl(const QString &role, const quint8 channel, const quint8 control);

    static MidiMapping *loadFromFile(const QString &filename);
    static void saveToFile(MidiMapping *mm, const QString& filename);

signals:
    
public slots:

private:
    QString _vendor;
    QString _product;
    QString _comment;
    bool _acceptClock;
    bool _acceptProgramChange;
    bool _acceptControlChange;
    bool _acceptNoteChange;
    QMap<QString,QVariant> _map;
    bool _modified;

    int _tracks;
    int _knobsPerTrack;
    int _triggersPerTrack;
};

#endif // MIDIMAPPING_H
