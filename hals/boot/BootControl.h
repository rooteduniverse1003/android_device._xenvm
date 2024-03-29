/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef ANDROID_HARDWARE_BOOT_V1_0_BOOTCONTROL_H
#define ANDROID_HARDWARE_BOOT_V1_0_BOOTCONTROL_H

#include <android/hardware/boot/1.0/IBootControl.h>
#include <hidl/Status.h>

#include <hidl/MQDescriptor.h>

#include "bootloader_message/bootloader_message.h"

/*#define AVB_AB_I_UNDERSTAND_LIBAVB_AB_IS_DEPRECATED

#include "libavb_ab/libavb_ab.h"*/

namespace android {
namespace hardware {
namespace boot {
namespace V1_0 {
namespace implementation {

using ::android::hardware::boot::V1_0::BoolResult;
using ::android::hardware::boot::V1_0::CommandResult;
using ::android::hardware::boot::V1_0::IBootControl;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::hidl_vec;
using ::android::hardware::hidl_string;
using ::android::sp;

/* Maximum values for slot data */
#define AVB_AB_MAX_PRIORITY 15
#define AVB_AB_MAX_TRIES_REMAINING 7

struct BootControl : public IBootControl {
    BootControl();
    // Methods from ::android::hardware::boot::V1_0::IBootControl follow.
    Return<uint32_t> getNumberSlots()  override;
    Return<uint32_t> getCurrentSlot()  override;
    Return<void> markBootSuccessful(markBootSuccessful_cb _hidl_cb)  override;
    Return<void> setActiveBootSlot(uint32_t slot, setActiveBootSlot_cb _hidl_cb)  override;
    Return<void> setSlotAsUnbootable(uint32_t slot, setSlotAsUnbootable_cb _hidl_cb)  override;
    Return<BoolResult> isSlotBootable(uint32_t slot)  override;
    Return<BoolResult> isSlotMarkedSuccessful(uint32_t slot)  override;
    Return<void> getSuffix(uint32_t slot, getSuffix_cb _hidl_cb)  override;
private:
    bool loadBootloaderControl(bootloader_control* data);
    bool saveBootloaderControl(bootloader_control* data);
    bool checkSlotIsBootable(slot_metadata* slot_data);
    uint32_t slotSuffixToIndex(const char* suffix);
    void setSlotUnbootable(slot_metadata* slotData);

    uint32_t mCurrentSlotIndex;

    static const uint32_t kAvbMaxSlots = 2;
    const char* avbAbSlotsSuffixes[kAvbMaxSlots] = { "_a", "_b" };
    const char* kMiscPath = "/dev/block/by-name/misc";
    const char* kAvbAbSlotSuffixProperty = "ro.boot.slot_suffix";
    const uint32_t AVB_AB_ERROR_SLOT_INDEX = 0xABCDFFFF;
};

extern "C" IBootControl* HIDL_FETCH_IBootControl(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace boot
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_BOOT_V1_0_BOOTCONTROL_H
