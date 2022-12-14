USE [RanShop]
GO
/****** Object:  Table [dbo].[LogShopPurchase]    Script Date: 10/25/2015 16:52:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LogShopPurchase](
	[PurNum] [bigint] IDENTITY(1,1) NOT NULL,
	[PurKey] [varchar](21) NOT NULL,
	[PurFlag] [int] NULL,
	[PurDate] [datetime] NULL CONSTRAINT [DF_LogShopPurchase_PurDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_LogShopPurchase] PRIMARY KEY CLUSTERED 
(
	[PurNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ShopPurFlag]    Script Date: 10/25/2015 16:52:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ShopPurFlag](
	[PurFlag] [int] NOT NULL,
	[PurFlagName] [varchar](20) NULL,
 CONSTRAINT [PK_ShopPurFlag] PRIMARY KEY CLUSTERED 
(
	[PurFlag] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ShopPurchase]    Script Date: 10/25/2015 16:52:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ShopPurchase](
	[PurKey] [bigint] IDENTITY(1,1) NOT NULL,
	[UserUID] [varchar](20) NOT NULL,
	[ProductNum] [int] NOT NULL,
	[PurPrice] [int] NOT NULL CONSTRAINT [DF_ShopPurchase_PurPrice]  DEFAULT ((0)),
	[PurFlag] [int] NOT NULL CONSTRAINT [DF_ShopPurchase_PurFlag]  DEFAULT ((0)),
	[PurDate] [datetime] NOT NULL CONSTRAINT [DF_ShopPurchase_PurDate]  DEFAULT (getdate()),
	[PurChgDate] [datetime] NULL,
 CONSTRAINT [PK_ShopPurchase] PRIMARY KEY CLUSTERED 
(
	[PurKey] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ShopItemMap]    Script Date: 10/25/2015 16:52:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ShopItemMap](
	[ProductNum] [int] IDENTITY(1,1) NOT NULL,
	[ItemMain] [int] NULL,
	[ItemSub] [int] NULL,
	[ItemName] [varchar](100) NULL,
	[ItemList] [smallint] NULL CONSTRAINT [DF_ShopItemMap_ItemList]  DEFAULT ((1)),
	[Duration] [varchar](50) NULL,
	[Category] [int] NULL,
	[ItemStock] [int] NOT NULL CONSTRAINT [DF__ShopItemM__ItemS__38996AB5]  DEFAULT ((0)),
	[ItemImage] [varchar](300) NULL,
	[ItemMoney] [int] NULL,
	[ItemComment] [varchar](50) NULL,
 CONSTRAINT [PK_ShopItemMap] PRIMARY KEY CLUSTERED 
(
	[ProductNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_purchase_change_state]    Script Date: 10/25/2015 16:52:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_purchase_change_state]
	@purkey varchar(22),
    @purflag int,
	@nReturn int OUTPUT
AS
	DECLARE 	
		@error_var int, -- Declare variables used in error checking.
		@rowcount_var int,
		@nFlag int

	SET NOCOUNT ON
	
	SET @nFlag = 0
	
	SELECT @nFlag=PurFlag 
	FROM ShopPurchase 
	WHERE PurKey=@purkey
	
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
	    SET @nReturn = 0
	    SET NOCOUNT OFF
	    RETURN @nReturn	
	END
	
	-- 官操妨绰 内靛客 泅犁 内靛啊 鞍篮 版快 俊矾
	IF @nFlag = @purflag
	BEGIN
	    SET @nReturn = 0
	    SET NOCOUNT OFF
	    RETURN @nReturn	
	END
	
	-- 沥犬窍霸 官曹荐 乐绰 版快
    UPDATE ShopPurchase
    SET PurFlag=@purflag, PurChgDate=getdate() 
    WHERE PurKey=@purkey

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
	    -- 角菩
	    SET @nReturn = 0
	END
    ELSE
    BEGIN
	    -- 己傍
	    INSERT INTO LogShopPurchase (PurKey, PurFlag) 
	    VALUES (@purkey, @purflag)
	    SET @nReturn = 1
    END

	SET NOCOUNT OFF

	RETURN @nReturn
GO
/****** Object:  View [dbo].[viewShopPurchase]    Script Date: 10/25/2015 16:52:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-------------------------------------------------------------------------------
-- viewShopPurchase
-------------------------------------------------------------------------------

CREATE VIEW [dbo].[viewShopPurchase]
AS
SELECT   dbo.ShopPurchase.PurKey, dbo.ShopPurchase.UserUID, 
         dbo.ShopPurchase.ProductNum, dbo.ShopPurchase.PurPrice, 
         dbo.ShopPurchase.PurFlag, dbo.ShopPurchase.PurDate, 
         dbo.ShopPurchase.PurChgDate, dbo.ShopItemMap.ItemMain, 
         dbo.ShopItemMap.ItemSub, dbo.ShopItemMap.ItemName, 
         dbo.ShopPurFlag.PurFlagName
FROM     dbo.ShopPurchase INNER JOIN
         dbo.ShopItemMap ON 
         dbo.ShopPurchase.ProductNum = dbo.ShopItemMap.ProductNum LEFT OUTER JOIN
         dbo.ShopPurFlag ON dbo.ShopPurchase.PurFlag = dbo.ShopPurFlag.PurFlag
GO
/****** Object:  StoredProcedure [dbo].[sp_InsertItem]    Script Date: 10/25/2015 16:52:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_InsertItem]
	@PurKey	varchar(100),
	@UserId varchar(50),
	@MID int,
	@SID int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@ProductNum int;

	SET NOCOUNT ON;
	
	SET @nReturn = -1;
	
	SELECT @ProductNum = ShopItemMap.ProductNum 
	FROM ShopItemMap
	WHERE ItemMain = @MID and ItemSub = @SID;

	IF @@ERROR <> 0 OR @@ROWCOUNT = 0
		BEGIN
			--item not found
			SET @nReturn = -1;
			SET NOCOUNT OFF
			RETURN @nReturn	
		END
	ELSE
		BEGIN
			INSERT INTO ShopPurchase ( UserUID, ProductNum, PurFlag, PurDate )
			VALUES( @UserId, @ProductNum, 0, GETDATE())
			IF @@ERROR = 0
			BEGIN 
				SET @nReturn = 0;
			END
		END
		
	SET NOCOUNT OFF;
	
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_purchase_insert_item]    Script Date: 10/25/2015 16:52:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_purchase_insert_item]
	@purkey varchar(22),
	@useruid varchar(30),
    @productnum int,
    @purprice int,
	@nReturn int OUTPUT
AS
	DECLARE 	
		@error_var int -- Declare variables used in error checking.

	SET NOCOUNT ON

	INSERT INTO ShopPurchase (PurKey, UserUID, ProductNum, PurPrice) 
	VALUES (@purkey, @useruid, @productnum, @purprice)

	SELECT @error_var = @@ERROR
	IF @error_var <> 0 
	BEGIN
	    -- 火涝角菩
	    SET @nReturn = 0	    
	END
        ELSE
        BEGIN
	    -- 沥惑利栏肺 火涝 己傍
	    SET @nReturn = 1
        END

	SET NOCOUNT OFF

	RETURN @nReturn
GO
/****** Object:  View [dbo].[viewShopPurchaseItem]    Script Date: 10/25/2015 16:52:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-------------------------------------------------------------------------------
-- view_ShopPurchaseItem.sql
-------------------------------------------------------------------------------

CREATE VIEW [dbo].[viewShopPurchaseItem]
AS
SELECT TOP 100 PERCENT SUM(A.PurPrice) AS tPrice, A.ItemMain, A.ItemSub, B.ItemName
FROM   dbo.viewShopPurchase A INNER JOIN
       dbo.ShopItemMap B ON A.ProductNum = B.ProductNum
GROUP BY A.ItemMain, A.ItemSub, B.ItemName
ORDER BY A.ItemMain, A.ItemSub
GO
