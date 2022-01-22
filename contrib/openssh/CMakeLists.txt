#
# cmake-format: off
# __legal_b__
#
# Copyright (c) 2022 Michel Gillet
# Distributed under the wxWindows Library Licence, Version 3.1.
# (See accompanying file LICENSE_3_1.txt or
# copy at http://www.wxwidgets.org/about/licence)
#
# __legal_e__
# cmake-format: on
#

cmake_minimum_required(VERSION 3.10)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

project(libopenssh C)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ../.. ../../openbsd-compat)

set(CONFIG_H_IN_DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/../../configure.ac")
set(CONFIG_H_IN_OUTPUT      "${CMAKE_CURRENT_SOURCE_DIR}/../../config.h.in")

add_custom_command(OUTPUT ${CONFIG_H_IN_OUTPUT}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../..
                    COMMAND autoreconf
                    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/temp
                    COMMAND ${CMAKE_COMMAND} -E touch ${CONFIG_H_IN_OUTPUT}
                    DEPENDS ${CONFIG_H_IN_DEPS})

add_custom_target(libopenssh_autoreconf ALL DEPENDS ${CONFIG_H_IN_OUTPUT})

set(CONFIG_H_DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/../../configure.ac")
set(CONFIG_H_OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/config.h")

add_custom_command(OUTPUT ${CONFIG_H_OUTPUT}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/temp
                    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../configure 
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/temp/config.h ${CONFIG_H_OUTPUT}
                    DEPENDS ${CONFIG_H_IN_OUTPUT})

add_custom_target(libopenssh_configure ALL DEPENDS ${CONFIG_H_OUTPUT})

set(LIBOPENSSH_XMSS_C_SOURCES
    ssh-xmss.c 
	sshkey-xmss.c 
	xmss_commons.c 
	xmss_fast.c
	xmss_hash.c 
	xmss_hash_address.c 
	xmss_wots.c
)

set(LIBOPENSSH_LIBOPENSSH_C_SOURCES
    ssh_api.c 
	ssherr.c 
	sshbuf.c 
	sshkey.c 
	sshbuf-getput-basic.c 
	sshbuf-misc.c 
	sshbuf-getput-crypto.c 
	krl.c
	bitmap.c
)

set(LIBOPENSSH_LIBSSH_C_SOURCES
    authfd.c 
    authfile.c
	canohost.c 
    channels.c 
    cipher.c 
    cipher-aes.c 
    cipher-aesctr.c
	cipher-ctr.c 
    cleanup.c 
	compat.c 
    fatal.c 
    hostfile.c 
	log.c 
    match.c 
    moduli.c 
    nchan.c 
    packet.c 
	readpass.c 
    ttymodes.c 
    xmalloc.c 
    addr.c 
    addrmatch.c
	atomicio.c 
    dispatch.c 
    mac.c 
    misc.c 
    utf8.c 
	monitor_fdpass.c 
    rijndael.c 
    ssh-dss.c 
    ssh-ecdsa.c 
    ssh-ecdsa-sk.c
	ssh-ed25519-sk.c 
    ssh-rsa.c 
    dh.c
	msg.c 
    progressmeter.c 
    dns.c 
    entropy.c 
    gss-genr.c 
    umac.c 
    umac128.c
	ssh-pkcs11.c 
    smult_curve25519_ref.c
	poly1305.c 
    chacha.c 
    cipher-chachapoly.c 
    cipher-chachapoly-libcrypto.c
	ssh-ed25519.c 
    digest-openssl.c 
    digest-libc.c 
	hmac.c 
    sc25519.c 
    ge25519.c 
    fe25519.c 
    ed25519.c 
    verify.c 
    hash.c 
	kex.c 
    kexdh.c 
    kexgex.c 
    kexecdh.c 
    kexc25519.c 
	kexgexc.c 
    kexgexs.c 
	kexsntrup761x25519.c 
    sntrup761.c 
    kexgen.c 
	sftp-realpath.c 
    platform-pledge.c 
    platform-tracing.c 
    platform-misc.c 
	sshbuf-io.c
    # Added 
    ssh-sk-client.c
)

set(LIBOPENSSH_OPENBSD_C_SOURCES
    base64.c 
	basename.c 
	bcrypt_pbkdf.c 
	bcrypt_pbkdf.c 
	bindresvport.c 
	blowfish.c
	daemon.c 
	dirname.c 
	explicit_bzero.c 
	fmt_scaled.c 
	freezero.c 
	fnmatch.c 
	getcwd.c 
	getgrouplist.c 
	getopt_long.c 
	getrrsetbyname.c 
	glob.c 
	inet_aton.c 
	inet_ntoa.c 
	inet_ntop.c 
	md5.c 
	memmem.c 
	mktemp.c 
	pwcache.c 
	readpassphrase.c 
	reallocarray.c 
	recallocarray.c 
	rresvport.c 
	setenv.c 
	setproctitle.c 
	sha1.c 
	sha2.c 
	sigact.c 
	strcasestr.c 
	strlcat.c 
	strlcpy.c 
	strmode.c 
	strndup.c 
	strnlen.c 
	strptime.c 
	strsep.c 
	strtoll.c 
	strtonum.c 
	strtoull.c 
	strtoul.c 
	timingsafe_bcmp.c 
	vis.c
)
list(TRANSFORM LIBOPENSSH_OPENBSD_C_SOURCES
     PREPEND ../../openbsd-compat/)

set(LIBOPENSSH_COMPAT_C_SOURCES
     arc4random.c
     bsd-asprintf.c 
     bsd-closefrom.c 
     bsd-cygwin_util.c 
     bsd-err.c 
     bsd-flock.c 
     bsd-getline.c 
     bsd-getpagesize.c 
     bsd-getpeereid.c
     bsd-malloc.c 
     bsd-misc.c 
     bsd-nextstep.c 
     bsd-openpty.c
     bsd-poll.c 
     bsd-setres_id.c
     bsd-signal.c 
     bsd-snprintf.c 
     bsd-statvfs.c 
     bsd-waitpid.c
     fake-rfc2553.c 
     getrrsetbyname-ldns.c 
     kludge-fd_set.c 
     openssl-compat.c 
     libressl-api-compat.c 
     xcrypt.c
)
list(TRANSFORM LIBOPENSSH_COMPAT_C_SOURCES
     PREPEND ../../openbsd-compat/)

set(LIBOPENSSH_PORTS_C_SOURCES
     # port-aix.c 
     # port-irix.c 
     port-linux.c 
     # port-solaris.c 
     port-net.c 
     # port-uw.c
)
list(TRANSFORM LIBOPENSSH_PORTS_C_SOURCES
     PREPEND ../../openbsd-compat/)


set(LIBOPENSSH_C_SOURCES  
    ${LIBOPENSSH_XMSS_C_SOURCES}
    ${LIBOPENSSH_LIBOPENSSH_C_SOURCES}
    ${LIBOPENSSH_LIBSSH_C_SOURCES}   
)
list(TRANSFORM LIBOPENSSH_C_SOURCES
     PREPEND ../../)

add_library(
  openssh SHARED
  ${LIBOPENSSH_C_SOURCES}
  ${LIBOPENSSH_OPENBSD_C_SOURCES}
  ${LIBOPENSSH_COMPAT_C_SOURCES}
  ${LIBOPENSSH_PORTS_C_SOURCES}
)

add_dependencies(openssh libopenssh_configure)

target_link_libraries(openssh crypto dl util z crypt resolv)
target_include_directories(openssh PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ../.. ../../openbsd-compat)

# SSH
set(SSH_C_SOURCES
    ssh.c 
    readconf.c 
    clientloop.c 
    sshtty.c 
    sshconnect.c 
    sshconnect2.c 
    mux.c 
    #$(SKOBJS)
)
list(TRANSFORM SSH_C_SOURCES
     PREPEND ../../)

add_executable(ssh ${SSH_C_SOURCES})

target_link_libraries(
    ssh PRIVATE openssh)


# SSHD
set(SSHD_C_SOURCES
    sshd.c
    auth-rhosts.c 
    auth-passwd.c
    audit.c 
    audit-bsm.c 
    audit-linux.c 
    platform.c
    sshpty.c 
    sshlogin.c 
    servconf.c 
    serverloop.c
    auth.c 
    auth2.c 
    auth-options.c 
    session.c
    auth2-chall.c 
    groupaccess.c
    auth-bsdauth.c 
    auth2-hostbased.c 
    auth2-kbdint.c
    auth2-none.c 
    auth2-passwd.c 
    auth2-pubkey.c 
    monitor.c 
    monitor_wrap.c 
    auth-krb5.c
    auth2-gss.c 
    gss-serv.c 
    gss-serv-krb5.c
    loginrec.c 
    auth-pam.c 
    auth-shadow.c 
    auth-sia.c 
    md5crypt.c
    srclimit.c 
    sftp-server.c 
    sftp-common.c
    sandbox-null.c 
    sandbox-rlimit.c 
    sandbox-systrace.c 
    sandbox-darwin.c
    sandbox-seccomp-filter.c 
    sandbox-capsicum.c 
    sandbox-pledge.c
    sandbox-solaris.c 
    uidswap.c
    #$(SKOBJS)
)
list(TRANSFORM SSHD_C_SOURCES
     PREPEND ../../)

add_executable(sshd ${SSHD_C_SOURCES})

target_link_libraries(sshd PRIVATE openssh)

# SCP
set(SCP_C_SOURCES
    scp.c 
    progressmeter.c
)
list(TRANSFORM SCP_C_SOURCES
     PREPEND ../../)

add_executable(scp ${SCP_C_SOURCES})

target_link_libraries(scp PRIVATE openssh)  
    
# SSH-ADD
set(SSH_ADD_C_SOURCES
    ssh-add.c 
    #$(SKOBJS)
)
list(TRANSFORM SSH_ADD_C_SOURCES
     PREPEND ../../)

add_executable(ssh-add ${SSH_ADD_C_SOURCES})

target_link_libraries(ssh-add PRIVATE openssh)   

# SSH-AGENT
set(SSH_AGENT_C_SOURCES
    ssh-agent.c 
    ssh-pkcs11-client.c 
    #$(SKOBJS)
)
list(TRANSFORM SSH_AGENT_C_SOURCES
     PREPEND ../../)

add_executable(ssh-agent ${SSH_AGENT_C_SOURCES})

target_link_libraries(ssh-agent PRIVATE openssh)   

# SSH-KEYGEN
set(SSH_KEYGEN_C_SOURCES
    ssh-keygen.c 
    sshsig.c 
    #$(SKOBJS)
)
list(TRANSFORM SSH_KEYGEN_C_SOURCES
     PREPEND ../../)

add_executable(ssh-keygen ${SSH_KEYGEN_C_SOURCES})

target_link_libraries(ssh-keygen PRIVATE openssh)   

# SSH-KEYSIGN
set(SSH_KEYSIGN_C_SOURCES
    ssh-keysign.c 
    readconf.c
    uidswap.c 
    #$(SKOBJS)
)
list(TRANSFORM SSH_KEYSIGN_C_SOURCES
     PREPEND ../../)

add_executable(ssh-keysign ${SSH_KEYSIGN_C_SOURCES})

target_link_libraries(ssh-keysign PRIVATE openssh)

# SSH-PKCS11-HELPER
set(SSH_PKCS11_HELPER_C_SOURCES
    ssh-pkcs11-helper.c 
    ssh-pkcs11.c 
    #$(SKOBJS)
)
list(TRANSFORM SSH_PKCS11_HELPER_C_SOURCES
     PREPEND ../../)

add_executable(ssh-pkcs11-helper ${SSH_PKCS11_HELPER_C_SOURCES})

target_link_libraries(ssh-pkcs11-helper PRIVATE openssh)

# SSH-SK-HELPER
set(SSH_SK_HELPER_C_SOURCES
    ssh-sk-helper.c 
    ssh-sk.c 
    sk-usbhid.c
)
list(TRANSFORM SSH_SK_HELPER_C_SOURCES
     PREPEND ../../)

add_executable(ssh-sk-helper ${SSH_SK_HELPER_C_SOURCES})

target_link_libraries(ssh-sk-helper PRIVATE openssh)

# SSH-KEYSCAN
set(SSH_KEYSCAN_C_SOURCES
    ssh-keyscan.c 
    #$(SKOBJS)
)
list(TRANSFORM SSH_KEYSCAN_C_SOURCES
     PREPEND ../../)

add_executable(ssh-keyscan ${SSH_KEYSCAN_C_SOURCES})

target_link_libraries(ssh-keyscan PRIVATE openssh)

# SFTP-SERVER
set(SFTP_SERVER_C_SOURCES
    sftp-common.c 
    sftp-server.c 
    sftp-server-main.c
)
list(TRANSFORM SFTP_SERVER_C_SOURCES
     PREPEND ../../)

add_executable(sftp-server ${SFTP_SERVER_C_SOURCES})

target_link_libraries(sftp-server PRIVATE openssh)

# SFTP
set(SFTP_C_SOURCES
    sftp.c 
    sftp-client.c 
    sftp-common.c 
    sftp-glob.c 
    progressmeter.c
)
list(TRANSFORM SFTP_C_SOURCES
     PREPEND ../../)

add_executable(sftp ${SFTP_C_SOURCES})

target_link_libraries(sftp PRIVATE openssh)

