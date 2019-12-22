

Component({
  properties: {
    propArray: {
      type: Array,
    },
    defalutSelect:{
      type:String
    }
  },
  data: {
  select: false,
    grade_name: '--请选择--',
    
  grades: ['00', '01', '02','03','04','05','06','07','08','09','10','11','12','13','14','15','16',
'17','18','19','20','21','22','23'
      ]
},/**
*  点击下拉框 */
methods:{
 bindShowMsg() {
  this.setData({
    select: !this.data.select
  })
},/**

* 已选下拉框 */

mySelect(e) {
  console.log(e);   this.setData({
    grade_name: e.currentTarget.dataset.name,
    
    select: false
  })
},
  upload (e) {
   // this.mySelect(e)
    // var value1=this.data.inputvalue1
    //var value2 = this.data.inputvalue2
    //console.log(value)
    //this.setData({
      //grade_name:grade_name,
    //})
   var name=this.data.grade_name
    if (name=='--请选择--') {
      wx.showModal({
        content: `亲，还没有输入时间哦`
      })
    }
    else if (name!= '--请选择--' ) {
      wx.showModal({
        content: `亲，您的订单已提交成功！`
      })
      wx.request({
        url: 'http://api.heclouds.com/devices/562233664/datapoints?type=3',
        method: 'post',
        header: {
          //"content-type": "application/x-www-form-urlencoded",
          "api-key": "7AHL6HLQEDOSQtTzwBMjw7kEuaw=",
        },
        success: function (res) {
          //console.log(util.formatTime)
          console.log(res)
        },
        data: {
          hour:name
        },
      })
    }
  }
},

})