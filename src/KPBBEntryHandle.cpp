/***************************************************************************
 *   Copyright (C) 2013 by Dan Samargiu                                    *
 *   samargiudan@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include "KPBBEntryHandle.h"

KPBBEntryHandle::KPBBEntryHandle() : mMutex() {
}

KPBBEntryHandle::KPBBEntryHandle(IEntryHandle* entryHandle) {
	this->mEntryHandle = entryHandle;
}

KpxUuid KPBBEntryHandle::uuid() const {
	return this->mEntryHandle->uuid();
}

IGroupHandle* KPBBEntryHandle::group() const {
	return this->mEntryHandle->group();
}

quint32 KPBBEntryHandle::image() const {
	return this->mEntryHandle->image();
}

int KPBBEntryHandle::visualIndex() const {
	return this->mEntryHandle->visualIndex();
}

QString KPBBEntryHandle::title() const {
	return this->mEntryHandle->title();
}

QString KPBBEntryHandle::url() const {
	return this->mEntryHandle->url();
}

QString KPBBEntryHandle::username() const {
	return this->mEntryHandle->username();
}

SecString KPBBEntryHandle::password() const {
	return this->mEntryHandle->password();
}

QString KPBBEntryHandle::passwordUnlocked() {
	QMutexLocker ml(&mMutex);
	SecString pass = this->password();
	pass.unlock();
	return QString(pass);
}

QString KPBBEntryHandle::comment() const {
	return this->mEntryHandle->comment();
}

QString KPBBEntryHandle::binaryDesc() const {
	return this->mEntryHandle->binaryDesc();
}

KpxDateTime KPBBEntryHandle::creation() const {
	return this->mEntryHandle->creation();
}

KpxDateTime KPBBEntryHandle::lastMod() const {
	return this->mEntryHandle->lastMod();
}

KpxDateTime KPBBEntryHandle::lastAccess() const {
	return this->mEntryHandle->lastAccess();
}

KpxDateTime KPBBEntryHandle::expire() const {
	return this->mEntryHandle->expire();
}

QByteArray KPBBEntryHandle::binary() const {
	return this->mEntryHandle->binary();
}

quint32 KPBBEntryHandle::binarySize() const {
	return this->mEntryHandle->binarySize();
}

QString KPBBEntryHandle::friendlySize() const {
	return this->mEntryHandle->friendlySize();
}

bool KPBBEntryHandle::isValid() const {
	return this->mEntryHandle->isValid();
}

CEntry KPBBEntryHandle::data() const {
	return this->mEntryHandle->data();
}

void KPBBEntryHandle::setImage(const quint32& imageId) {
	this->mEntryHandle->setImage(imageId);
}

void KPBBEntryHandle::setVisualIndex(int i) {
	this->mEntryHandle->setVisualIndex(i);
}

void KPBBEntryHandle::setTitle(const QString& title) {
	this->mEntryHandle->setTitle(title);
}

void KPBBEntryHandle::setUrl(const QString& url) {
	this->mEntryHandle->setUrl(url);
}

void KPBBEntryHandle::setUsername(const QString& username) {
	this->mEntryHandle->setUsername(username);
}

void KPBBEntryHandle::setPassword(const SecString& password) {
	this->mEntryHandle->setPassword(password);
}

void KPBBEntryHandle::setComment(const QString& comment) {
	this->mEntryHandle->setComment(comment);
}

void KPBBEntryHandle::setBinaryDesc(const QString& binaryDesc) {
	this->mEntryHandle->setBinaryDesc(binaryDesc);
}

void KPBBEntryHandle::setCreation(const KpxDateTime& creation) {
	this->mEntryHandle->setCreation(creation);
}

void KPBBEntryHandle::setLastMod(const KpxDateTime& lastMod) {
	this->mEntryHandle->setLastMod(lastMod);
}

void KPBBEntryHandle::setLastAccess(const KpxDateTime& lastAccess) {
	this->mEntryHandle->setLastAccess(lastAccess);
}

void KPBBEntryHandle::setExpire(const KpxDateTime& expire) {
	this->mEntryHandle->setExpire(expire);
}

void KPBBEntryHandle::setBinary(const QByteArray& binaryData) {
	this->mEntryHandle->setBinary(binaryData);
}

void KPBBEntryHandle::setVisualIndexDirectly(int i) {
	this->mEntryHandle->setVisualIndexDirectly(i);
}

void KPBBEntryHandle::copyPasswordToClipboard()
{
	bb::system::Clipboard clipboard;
	clipboard.clear();
	QString pw(this->passwordUnlocked());
	QByteArray b;
	b.append(pw);
	clipboard.insert("text/plain", b);
}

void KPBBEntryHandle::copyUsernameToClipboard()
{
	bb::system::Clipboard clipboard;
	clipboard.clear();
	QString un(this->username());
	QByteArray b;
	b.append(un);
	clipboard.insert("text/plain", b);
}

void KPBBEntryHandle::launchBrowser()
{
	bb::system::InvokeManager invokeManager;
	bb::system::InvokeRequest request;
	// Set the URI
	QString uri = this->url();
	if (!uri.startsWith("http://") &&
		!uri.startsWith("https://") &&
		!uri.startsWith("ftp://"))
	{
		uri.prepend("http://");
	}

	request.setUri(uri);
	request.setTarget("sys.browser");
	request.setAction("bb.action.OPEN");
	// Send the invoke
	bb::system::InvokeTargetReply *reply = invokeManager.invoke(request);
}
