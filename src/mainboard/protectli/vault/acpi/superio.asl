#include "onboard.h"

	Device (COM1) {
		Name (_HID, EISAID ("PNP0501"))
		Name (_UID, One)
		Name (_ADR, 0)

		Method (_STA, 0, NotSerialized) {
			Return (0x0F)
		}

		Name (_CRS, ResourceTemplate () {
			FixedIO (0x03F8, 0x08)
			IRQNoFlags () {4}
		})

		Name (_PRS, ResourceTemplate () {
			StartDependentFn (0, 0) {
				FixedIO (0x03F8, 0x08)
				IRQNoFlags () {4}
			}
			EndDependentFn ()
		})
	}
