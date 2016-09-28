using UnityEngine;
using System.Collections;
using Vuforia;

public class CameraFocus : MonoBehaviour {
    public bool focusModeSet;

	void Start () {
        VuforiaBehaviour.Instance.RegisterVuforiaStartedCallback(OnVuforiaStarted);
        VuforiaBehaviour.Instance.RegisterOnPauseCallback(OnPaused);
	}
	
    private void OnVuforiaStarted()
    {
        focusModeSet = CameraDevice.Instance.SetFocusMode(
                CameraDevice.FocusMode.FOCUS_MODE_CONTINUOUSAUTO);
        // FOCUS_MODE_TRIGGERAUTO   // touch to focus
        // https://developer.vuforia.com/library/articles/Solution/Camera-Focus-Modes
    }

    private void OnPaused(bool paused)
    {
        if (!paused)
        {
            focusModeSet = CameraDevice.Instance.SetFocusMode(
                CameraDevice.FocusMode.FOCUS_MODE_CONTINUOUSAUTO);
        }
    }
}
