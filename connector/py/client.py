import asyncio

GBA_SOCKET_PORT = 43053

EXPECTED_SCRIPT_VERSION = 1

CONNECTION_STATUS_TIMING_OUT = (
    "Connection timing out. Please restart your emulator and connector_fe8.lua."
)
CONNECTION_STATUS_REFUSED = (
    "Connection refused. Please start your emulator and connector_fe8.lua."
)
CONNECTION_STATUS_RESET = (
        "Connection reset. Please restart your emulator and connector_fe8.lua."
)
CONNECTION_STATUS_TENTATIVE = "Initial connection made"
CONNECTION_STATUS_CONNECTED = "Connected"
CONNECTION_STATUS_INITIAL = "Connection has not been initiated"

class GBACommandProcessor(ClientCommandProcessor):
    def _cmd_gba(self) -> None:
        """Check GBA Connection State"""
        if isinstance(self.ctx, GBAContext):
            logger.info(f"GBA Status: {self.ctx.gba_status}")

class GBAContext(CommonContext):
    game = "Fire Emblem Sacred Stones"
    command_processor = GBACommandProcessor
    items_handling = 1
