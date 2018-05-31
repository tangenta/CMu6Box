#include "songinfo_win.h"
#include "playing-win/playlistedit_win.h"
#include <QAudioDecoder>

static const Position infoPos(5, 20);

SongInfoWin::SongInfoWin(Resources* res, QMediaContent /*cont*/)
    : Window(res) {
    //// TODO: show the information of a song
//    QMediaResource obj = cont.canonicalResource();
//    QAudioDecoder decoder;
//    decoder.setSourceFilename(obj.url().toLocalFile());

//    QAudioFormat format = decoder.audioFormat();
//    info = "Information:\n\n";
    QString totalInfo;

//    // always invalid..
//    totalInfo += "validation: " + (format.isValid() ? QString("valid") : QString("invalid")) + "\n";
//    totalInfo += "audio codec: " + obj.audioCodec() + "\n";
//    totalInfo += "channel count: " + QString::number(obj.channelCount()) + "\n";
//    totalInfo += "data size: " + QString::number(obj.dataSize()) + "\n";
//    totalInfo += "language: " + obj.language() + "\n";
//    totalInfo += "mime type: " + obj.mimeType() + "\n";
//    totalInfo += "sample rate: " + QString::number(obj.sampleRate()) + "\n";
//    totalInfo += "URL: " + obj.url().toDisplayString();

    // test dialog
    for (int i = 0; i != 30; ++i) {
        totalInfo += "testing" + QString::number(i) + "\n";
    }
    info += totalInfo.toStdString();
    dialog = Dialog(info, 40, 15, normal);
    dialog.setHighlight(highlight);
}

SongInfoWin::~SongInfoWin() {}

Window* SongInfoWin::handleInput(int ch) {
    if (ch == NK::Esc || ch == NK::Enter) {
        return new PlaylistWin(resource);
    } else if (ch == NK::Down) {
        dialog.moveDown();
    } else if (ch == NK::Up) {
        dialog.moveUp();
    } else if (ch == NK::Left) {
        dialog.focusCancel();
    } else if (ch == NK::Right) {
        dialog.focusOk();
    }
    return this;
}

void SongInfoWin::update() {}

void SongInfoWin::draw() {
    NBorder bord('=', '|', '+');
    bord.fit(dialog);
    Window::draw(NBlock<Dialog, NBorder>(dialog, bord), infoPos);
}
