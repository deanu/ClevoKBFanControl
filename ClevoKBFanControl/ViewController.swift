//
//  ViewController.swift
//  ClevoKBFanControl
//
//  Created by deanu on 2018/9/1.
//  Copyright © 2018年 deanu. All rights reserved.
//
import Cocoa

let on = 1
let off = 0

class ViewController: NSViewController {
    @IBOutlet weak var colorValue: NSTextField!
    @IBOutlet var errShow: NSTextView!
    @IBOutlet weak var onBtn: NSButton!
    @IBOutlet weak var offBtn: NSButton!
    @IBOutlet weak var modePop: NSPopUpButton!
    @IBOutlet weak var modeCheck: NSButton!
    @IBOutlet weak var brightnessPop: NSPopUpButton!
    @IBOutlet weak var brightnessCheck: NSButton!
    @IBOutlet weak var leftKb: NSTextField!
    @IBOutlet weak var cenKb: NSTextField!
    @IBOutlet weak var rightKb: NSTextField!
    @IBOutlet weak var autoCheck: NSButton!
    @IBOutlet weak var selfCheck: NSButton!
    @IBOutlet weak var useCheck: NSButton!
    @IBOutlet weak var startTemp: NSTextField!
    @IBOutlet weak var stopTemp: NSTextField!
    @IBOutlet weak var maxSpeed: NSTextField!
    @IBOutlet weak var colorWell: NSColorWell!

    @IBAction func setColor(_ sender: NSColorWell) {
        colorValue.stringValue = colorWell.color.toHexString()
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }

    @IBAction func invokeCmd(_ sender: Any) {

        var cmdout:String = ""
        var lightonflag = true
        var kbcolor = true
        var modeflag = true
        
        let hexstr = colorValue.stringValue
        let leftstr = leftKb.stringValue
        let censtr = cenKb.stringValue
        let rightstr = rightKb.stringValue
        let sepstr = leftstr + censtr + rightstr
        let startstr = startTemp.stringValue
        let stopstr = stopTemp.stringValue
        let maxstr = maxSpeed.stringValue
        
        
        if lightSwitch() == "OFF" {
            setlightSwitch(0)
            lightonflag = false
            cmdout = cmdout + "键盘灯：OFF\t"
        }
        
        if lightonflag {
            setlightSwitch(1)
            cmdout = cmdout + "键盘灯：ON\t"
            if brightnessCheck.state.rawValue == 1 {
                setkbBrightness(Int32(brightnessPop.indexOfSelectedItem))
                cmdout = cmdout + "亮度：" + String(brightnessPop.indexOfSelectedItem) + "\t"
            }
            
            if !leftstr.isEmpty && !censtr.isEmpty && !rightstr.isEmpty {
                if leftstr.count == 6 && censtr.count == 6 && rightstr.count == 6{
                    let sepcolor = UnsafeMutablePointer<Int8>(mutating: sepstr)
                    setsepcolor(sepcolor)
                    cmdout = cmdout + "颜色：分区域\t"
                    modeflag = false
                    kbcolor = false
                }
                else{
                    cmdout = cmdout + "分区域颜色设置错误！\t"
                }
            }
            if kbcolor {
                if !hexstr.isEmpty {
                    if hexstr.count == 6 {
                        let color = UnsafeMutablePointer<Int8>(mutating: hexstr)
                        setfullcolor(color)
                        cmdout = cmdout + "颜色：全键盘\t"
                        modeflag = false
                    }
                    else{
                        cmdout = cmdout + "全键盘颜色设置错误！\t"
                    }
                }
            }
            
            if modeCheck.state.rawValue == 1 {
                if modeflag {
                    if Int32(modePop.indexOfSelectedItem) == 0{
                        let hexstr = "0000FF"
                        let color = UnsafeMutablePointer<Int8>(mutating: hexstr)
                        setfullcolor(color)
                        
                    }
                    else{
                        setkbMode(Int32(modePop.indexOfSelectedItem))
                    }
                    cmdout = cmdout + "模式:" + modePop.itemTitle(at: modePop.indexOfSelectedItem) + "\t"
                }
            }
        }
        
        if useCheck.state.rawValue == 1 {
            if autoCheck.state.rawValue == 1 {
                setmbautoFan()
                cmdout = cmdout + "速度：AUTO\t"
            }
            else if selfCheck.state.rawValue == 1 {
                setmbFan(Int32(Int(startstr)!),Int32(stopstr)!,Int32(maxstr)!)
                cmdout = cmdout + "速度：自定义\t"
            }
        }
        errShow.string =  cmdout
    }
    
    @IBAction func onAct(_ sender: Any) {
        if onBtn.state.rawValue == on {
            offBtn.state = NSControl.StateValue(rawValue: off)
        }
        setlightSwitch(1)
    }
    
    @IBAction func offAct(_ sender: Any) {
        if offBtn.state.rawValue == on {
            onBtn.state = NSControl.StateValue(rawValue: off)
        }
        setlightSwitch(0)
    }
    
    @IBAction func autoAct(_ sender: Any) {
        if autoCheck.state.rawValue == on {
            selfCheck.state = NSControl.StateValue(rawValue: off)
        }
    }
    
    @IBAction func selfAct(_ sender: Any) {
        if selfCheck.state.rawValue == on {
            autoCheck.state = NSControl.StateValue(rawValue: off)
        }
    }
    
    func lightSwitch() -> String {
        if offBtn.state.rawValue == on {
            return "OFF"
        }
        return "ON"
    }
    
    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }
}

extension NSColor {

    func toHexString() -> String {
        var r:CGFloat = 0
        var g:CGFloat = 0
        var b:CGFloat = 0
        var a:CGFloat = 0
        getRed(&r, green: &g, blue: &b, alpha: &a)
        let rgb:Int = (Int)(r*255)<<16 | (Int)(g*255)<<8 | (Int)(b*255)<<0
        return String(format:"%06x", rgb)
    }
}
