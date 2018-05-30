#include "songinfo_win.h"
#include "playing-win/playlistedit_win.h"
#include <QMediaContent>
#include "../ncurse-wrap/util_nblock.h"
#include "../ncurse-wrap/util_nmenu.h"
#include "../ncurse-wrap/util_nborder.h"
#include "../ncurse-wrap/util_dialog.h"
#include <QAudioDecoder>

static const Position infoPos(5, 20);

SongInfoWin::SongInfoWin(Resources* res, QMediaContent cont)
    : Window(res) {
    //// TODO: show the information of a song
    QMediaResource obj = cont.canonicalResource();
    QAudioDecoder decoder;
    decoder.setSourceFilename(obj.url().toLocalFile());

    QAudioFormat format = decoder.audioFormat();
    info = "Information:\n\n";
    QString totalInfo;

    // always invalid..
    totalInfo += "validation: " + (format.isValid() ? QString("valid") : QString("invalid")) + "\n";
    totalInfo += "audio codec: " + obj.audioCodec() + "\n";
    totalInfo += "channel count: " + QString::number(obj.channelCount()) + "\n";
    totalInfo += "data size: " + QString::number(obj.dataSize()) + "\n";
    totalInfo += "language: " + obj.language() + "\n";
    totalInfo += "mime type: " + obj.mimeType() + "\n";
    totalInfo += "sample rate: " + QString::number(obj.sampleRate()) + "\n";
    totalInfo += "URL: " + obj.url().toDisplayString();

    info += totalInfo.toStdString();
}

SongInfoWin::~SongInfoWin() {}

Window* SongInfoWin::handleInput(int ch) {
    if (ch == NK::Esc) {
        return new PlaylistWin(resource);
    }
    return this;
}

void SongInfoWin::update() {}

void SongInfoWin::draw() {
    Window::draw(Dialog(info, 40, 15, normal), infoPos);
}
