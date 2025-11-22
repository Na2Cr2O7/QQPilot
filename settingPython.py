# -*- coding: utf-8 -*-

###########################################################################
## Python code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
## http://www.wxformbuilder.org/
##
## PLEASE DO *NOT* EDIT THIS FILE!
###########################################################################

import wx
import wx.xrc
import wx.richtext

import gettext
_ = gettext.gettext

###########################################################################
## Class MyFrame1
###########################################################################

class MyFrame1 ( wx.Frame ):

    def __init__( self, parent ):
        wx.Frame.__init__ ( self, parent, id = wx.ID_ANY, title = _(u"设置"), pos = wx.DefaultPosition, size = wx.Size( 740,386 ), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL, name = u"0" )

        self.SetSizeHints( wx.DefaultSize, wx.DefaultSize )
        self.SetFont( wx.Font( 9, wx.FONTFAMILY_SWISS, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL, False, "微软雅黑" ) )
        # self.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_MENU ) )
        self.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_MENU ) )

        gSizer3 = wx.GridSizer( 1, 2, 0, 0 )

        bSizer10 = wx.BoxSizer( wx.VERTICAL )

        bSizer2 = wx.BoxSizer( wx.VERTICAL )

        bSizer2.SetMinSize( wx.Size( -1,50 ) )
        bSizer1 = wx.BoxSizer( wx.HORIZONTAL )

        self.m_staticText1 = wx.StaticText( self, wx.ID_ANY, _(u"宽度"), wx.DefaultPosition, wx.DefaultSize, 0 )
        self.m_staticText1.Wrap( -1 )

        bSizer1.Add( self.m_staticText1, 0, wx.ALL, 5 )

        self.WindowWidth = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.Size( 300,-1 ), 0 )
        self.WindowWidth.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BACKGROUND ) )
        self.WindowWidth.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_WINDOW ) )
        self.WindowWidth.SetMinSize( wx.Size( 100,-1 ) )
        self.WindowWidth.SetMaxSize( wx.Size( 300,100 ) )

        bSizer1.Add( self.WindowWidth, 0, wx.ALL, 5 )

        self.m_staticText11 = wx.StaticText( self, wx.ID_ANY, _(u"高度"), wx.DefaultPosition, wx.DefaultSize, 0 )
        self.m_staticText11.Wrap( -1 )

        bSizer1.Add( self.m_staticText11, 0, wx.ALL, 5 )

        self.windowHeight = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.Size( 100,-1 ), 0 )
        self.windowHeight.SetMaxLength( 4 )
        self.windowHeight.SetMinSize( wx.Size( 100,-1 ) )

        bSizer1.Add( self.windowHeight, 0, wx.ALL, 5 )


        bSizer2.Add( bSizer1, 1, wx.EXPAND, 5 )

        bSizer61 = wx.BoxSizer( wx.HORIZONTAL )

        self.m_staticText111 = wx.StaticText( self, wx.ID_ANY, _(u"模型名称"), wx.DefaultPosition, wx.DefaultSize, 0 )
        self.m_staticText111.Wrap( -1 )

        bSizer61.Add( self.m_staticText111, 0, wx.ALL, 5 )

        self.modelName = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.Size( 888,-1 ), 0 )
        bSizer61.Add( self.modelName, 0, wx.ALL, 5 )


        bSizer2.Add( bSizer61, 1, wx.EXPAND, 5 )


        bSizer10.Add( bSizer2, 1, wx.EXPAND, 5 )

        bSizer15 = wx.BoxSizer( wx.VERTICAL )

        bSizer611 = wx.BoxSizer( wx.HORIZONTAL )

        self.m_staticText1111 = wx.StaticText( self, wx.ID_ANY, _(u"api key"), wx.DefaultPosition, wx.DefaultSize, 0 )
        self.m_staticText1111.Wrap( -1 )

        bSizer611.Add( self.m_staticText1111, 0, wx.ALL, 5 )

        self.apikey = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.Size( 400,-1 ), wx.TE_PASSWORD )
        bSizer611.Add( self.apikey, 0, wx.ALL, 5 )

        self.m_checkBox1 = wx.CheckBox( self, wx.ID_ANY, _(u"ollama"), wx.DefaultPosition, wx.Size( 100,-1 ), 0 )
        self.m_checkBox1.SetMinSize( wx.Size( 100,-1 ) )

        bSizer611.Add( self.m_checkBox1, 0, wx.ALL, 5 )


        bSizer15.Add( bSizer611, 1, wx.EXPAND, 5 )

        bSizer6111 = wx.BoxSizer( wx.HORIZONTAL )

        self.m_staticText11111 = wx.StaticText( self, wx.ID_ANY, _(u"服务器"), wx.DefaultPosition, wx.DefaultSize, 0 )
        self.m_staticText11111.Wrap( -1 )

        bSizer6111.Add( self.m_staticText11111, 0, wx.ALL, 5 )

        self.serverName = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.Size( -1,-1 ), 0 )
        self.serverName.SetMinSize( wx.Size( 500,-1 ) )

        bSizer6111.Add( self.serverName, 0, wx.ALL, 5 )


        bSizer15.Add( bSizer6111, 1, wx.EXPAND, 5 )


        bSizer10.Add( bSizer15, 1, wx.EXPAND, 5 )

        bSizer24 = wx.BoxSizer( wx.VERTICAL )

        bSizer61111 = wx.BoxSizer( wx.HORIZONTAL )

        self.m_staticText111111 = wx.StaticText( self, wx.ID_ANY, _(u"滚动次数"), wx.DefaultPosition, wx.DefaultSize, 0 )
        self.m_staticText111111.Wrap( -1 )

        bSizer61111.Add( self.m_staticText111111, 0, wx.ALL, 5 )

        self.scrollTries = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.Size( -1,-1 ), 0 )
        self.scrollTries.SetMaxLength( 2 )
        self.scrollTries.SetMinSize( wx.Size( 100,-1 ) )

        bSizer61111.Add( self.scrollTries, 0, wx.ALL, 5 )

        self.containsImage = wx.CheckBox( self, wx.ID_ANY, _(u"包含图片"), wx.DefaultPosition, wx.DefaultSize, 0 )
        bSizer61111.Add( self.containsImage, 0, wx.ALL, 5 )


        bSizer24.Add( bSizer61111, 1, wx.EXPAND, 5 )

        bSizer26 = wx.BoxSizer( wx.HORIZONTAL )

        self.autoLogin = wx.CheckBox( self, wx.ID_ANY, _(u"自动登录"), wx.DefaultPosition, wx.DefaultSize, 0 )
        bSizer26.Add( self.autoLogin, 0, wx.ALL, 5 )

        self.autoFocus = wx.CheckBox( self, wx.ID_ANY, _(u"持续将窗口置于最前"), wx.DefaultPosition, wx.DefaultSize, 0 )
        bSizer26.Add( self.autoFocus, 0, wx.ALL, 5 )

        self.cleanImageFile = wx.Button( self, wx.ID_ANY, _(u"清理图片文件"), wx.DefaultPosition, wx.DefaultSize, 0 )
        bSizer26.Add( self.cleanImageFile, 0, wx.ALL, 5 )


        bSizer24.Add( bSizer26, 1, wx.EXPAND, 5 )

        self.m_staticText28 = wx.StaticText( self, wx.ID_ANY, _(u"在Images目录下放置图片。"), wx.DefaultPosition, wx.DefaultSize, 0 )
        self.m_staticText28.Wrap( -1 )

        bSizer24.Add( self.m_staticText28, 0, wx.ALL, 5 )


        bSizer10.Add( bSizer24, 1, wx.EXPAND, 5 )


        bSizer10.Add( ( 0, 0), 1, wx.EXPAND, 1 )

        bSizer151 = wx.BoxSizer( wx.HORIZONTAL )

        self.OK = wx.Button( self, wx.ID_ANY, _(u"确定"), wx.DefaultPosition, wx.DefaultSize, 0 )
        bSizer151.Add( self.OK, 0, wx.ALL, 5 )

        self.A = wx.Button( self, wx.ID_ANY, _(u"应用"), wx.DefaultPosition, wx.DefaultSize, 0 )
        bSizer151.Add( self.A, 0, wx.ALL, 5 )

        self.Cancel = wx.Button( self, wx.ID_ANY, _(u"取消"), wx.DefaultPosition, wx.DefaultSize, 0 )
        bSizer151.Add( self.Cancel, 0, wx.ALL, 5 )


        bSizer10.Add( bSizer151, 1, wx.EXPAND, 5 )


        gSizer3.Add( bSizer10, 1, wx.EXPAND, 5 )

        bSizer13 = wx.BoxSizer( wx.VERTICAL )

        self.m_staticText9 = wx.StaticText( self, wx.ID_ANY, _(u"提示文本"), wx.DefaultPosition, wx.DefaultSize, 0 )
        self.m_staticText9.Wrap( -1 )

        bSizer13.Add( self.m_staticText9, 0, wx.ALL, 5 )

        self.intoText = wx.richtext.RichTextCtrl( self, wx.ID_ANY, _(u"1"), wx.DefaultPosition, wx.DefaultSize, 0|wx.VSCROLL|wx.HSCROLL|wx.NO_BORDER|wx.WANTS_CHARS )
        self.intoText.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_WINDOWTEXT ) )

        bSizer13.Add( self.intoText, 1, wx.EXPAND |wx.ALL, 5 )


        gSizer3.Add( bSizer13, 1, wx.EXPAND, 5 )


        self.SetSizer( gSizer3 )
        self.Layout()

    def __del__( self ):
        pass

if __name__ == "__main__":
    app = wx.App()
    frame = MyFrame1(None)
    frame.Show()
    app.MainLoop()


