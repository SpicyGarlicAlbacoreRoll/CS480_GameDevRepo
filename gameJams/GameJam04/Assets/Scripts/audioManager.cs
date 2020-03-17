using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class audioManager : MonoBehaviour
{
    // Start is called before the first frame update
    public AudioClip resultScreenMusic;

    public void Start() {

    }

    public void gameOver() {
        GetComponent<AudioSource>().Stop();
        GetComponent<AudioSource>().clip = resultScreenMusic;
        GetComponent<AudioSource>().loop = true;
        GetComponent<AudioSource>().pitch = 1.0f;
        GetComponent<AudioSource>().Play();
    }

}
