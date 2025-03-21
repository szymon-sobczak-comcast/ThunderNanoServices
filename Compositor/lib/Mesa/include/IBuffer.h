
/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 Metrological B.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "CompositorTypes.h"

#include <interfaces/IComposition.h>
#include <interfaces/ICompositionBuffer.h>

namespace WPEFramework {

namespace Compositor {

    struct ICallback
    {
        virtual ~ICallback() = default;
        virtual void LastFrameTimestamp(const uint64_t time) = 0;
    }; // struct ICallback

    /**
     * @brief  Allocate a new output.
     *         When the callee is done with the output, they must release it.
     *
     *
     * @param connector  Identification of the a output like a connector name 'card1-HDMI-A-1' or 'wayland-0'
     * @param width  Width in pixels
     * @param height Height in pixels
     * @param format Pixel layout for this buffer
     *
     * @return Core::ProxyType<Exchange::ICompositionBuffer> The allocated buffer
     */
    EXTERNAL Core::ProxyType<Exchange::ICompositionBuffer> Connector(
        const string& connector,
        const Exchange::IComposition::ScreenResolution resolution,
        const Compositor::PixelFormat& format,
        bool forceResolution,
        ICallback* callback = nullptr);

    /**
     * @brief  Allocate a new buffer.
     *         When the caller is done with the buffer, they must release it.
     *
     * @param width  Width in pixels
     * @param height Height in pixels
     * @param format Pixel layout for this buffer
     *
     * @return Core::ProxyType<Exchange::ICompositionBuffer> The allocated buffer
     */
    EXTERNAL Core::ProxyType<Exchange::ICompositionBuffer> CreateBuffer(
        const Identifier identifier,
        const uint32_t width,
        const uint32_t height,
        const PixelFormat& format);

} // namespace Compositor
} // namespace WPEFramework 
