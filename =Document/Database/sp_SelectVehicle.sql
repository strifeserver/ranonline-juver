set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
GO


ALTER PROCEDURE [dbo].[sp_SelectVehicle]
	@nVehicleNum		int,
	@nVehicleChaNum		int
AS
	SET NOCOUNT ON
	
	SELECT VehicleChaNum, VehicleCardMID, VehicleCardSID,
	VehicleType, VehicleBattery, VehicleBooster FROM VehicleInfo WHERE VehicleNum = @nVehicleNum And VehicleChaNum = @nVehicleChaNum

	SET NOCOUNT OFF	

