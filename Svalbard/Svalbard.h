/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Metrological
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

#include "Module.h"
#include <cryptography/cryptography.h>
#include <interfaces/IConfiguration.h>

namespace WPEFramework {
namespace Plugin {

    class Svalbard : public PluginHost::IPlugin {
    private:
        class Notification : public RPC::IRemoteConnection::INotification {
        public:
            Notification() = delete;
            Notification(const Notification&) = delete;
            Notification& operator=(const Notification&) = delete;

            explicit Notification(Svalbard& parent)
                : _parent(parent) {
            }
            ~Notification() override = default;

        public:
            void Activated(RPC::IRemoteConnection* /* connection */) override {
            }
            virtual void Deactivated(RPC::IRemoteConnection* connection) override {
                _parent.Deactivated(connection);
            }
            void Terminated(RPC::IRemoteConnection* /* connection */) override {
            }

            BEGIN_INTERFACE_MAP(Notification)
                INTERFACE_ENTRY(RPC::IRemoteConnection::INotification)
            END_INTERFACE_MAP

        private:
            Svalbard& _parent;
        };

    public:
        Svalbard(const Svalbard&) = delete;
        Svalbard& operator=(const Svalbard&) = delete;

PUSH_WARNING(DISABLE_WARNING_THIS_IN_MEMBER_INITIALIZER_LIST)
        Svalbard()
            : _connectionId(0)
            , _service(nullptr)
            , _svalbard(nullptr)
            , _notification(*this) {
        }
POP_WARNING()
        ~Svalbard() override = default;

        BEGIN_INTERFACE_MAP(Svalbard)
            INTERFACE_ENTRY(PluginHost::IPlugin)
            INTERFACE_AGGREGATE(Exchange::IDeviceObjects, _svalbard)
        END_INTERFACE_MAP

    public:
        //   IPlugin methods
        // -------------------------------------------------------------------------------------------------------
        const string Initialize(PluginHost::IShell* service) override;
        void Deinitialize(PluginHost::IShell* service) override;
        string Information() const override;
    
    private:
        void Deactivated(RPC::IRemoteConnection* connection);

    private:
        uint32_t _connectionId;
        PluginHost::IShell* _service;
        Exchange::IConfiguration* _svalbard;
        Core::Sink<Notification> _notification;
    };

} // Namespace Plugin.
}
