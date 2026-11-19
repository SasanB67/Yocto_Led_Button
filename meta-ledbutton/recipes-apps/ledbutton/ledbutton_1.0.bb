SUMMARY = "Turn an LED on while a push button is pressed (libgpiod)"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://ledbutton.c file://ledbutton.service"
S = "${WORKDIR}"

DEPENDS = "libgpiod"

inherit systemd
SYSTEMD_SERVICE:${PN} = "ledbutton.service"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ledbutton.c -o ledbutton -lgpiod
}

do_install() {
    install -D -m 0755 ledbutton ${D}${bindir}/ledbutton
    install -D -m 0644 ledbutton.service ${D}${systemd_system_unitdir}/ledbutton.service
}
