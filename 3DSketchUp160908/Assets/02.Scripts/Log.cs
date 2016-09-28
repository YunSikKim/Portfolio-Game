using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class Log : MonoBehaviour {
    public Transform cam, target;
    Text log;

	void Start () {
        log = GetComponent<Text>();
        cam = GameObject.Find("ARCamera").transform;
        target = GameObject.Find("ImageTarget").transform;
	}
	
	void Update () {
//        log = GetComponent<Text>();
//        float rotX = cam.rotation.x * 180.0f;
//        float rotY = cam.rotation.y * 180.0f;
//        float rotZ = cam.rotation.z * 180.0f;
//        log.text = "\n X : " + rotX.ToString();
//        log.text += "\n Y : " + rotY.ToString();
//        log.text += "\n Z : " + rotZ.ToString();
//
//        if (-65.0f <= rotY && rotY <= 65.0f)
//            log.text += "\n << FRONT >>";
//        else if (-150.0f <= rotY && rotY <= -65.0f)
//        {
//            if (rotX < 0) // 음수. -160.0f <= rotY && rotY <= -110
//                log.text += "\n << LEFT >>";
//            else
//                log.text += "\n << RIGHT >>";
//        }
//        else if (65.0f < rotY && rotY <= 130.0f)
//            log.text += "\n << LEFT >>";
//        else //if (rotY <= -150.0f)
//            log.text += "\n << BACK >>";
	}
}
