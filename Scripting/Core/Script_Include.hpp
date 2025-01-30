#pragma once

#include "pch.h"

#include "Include.hpp"

#include "Scripting.hpp"

#undef LOG
#undef FLUSH
#undef SESSION

#define EXPORT(cls_name) extern "C" __declspec(dllexport) cls_name* scriptInstance() { return new cls_name(); }

#define LOG this->session->log()
#define FLUSH this->session->flush()