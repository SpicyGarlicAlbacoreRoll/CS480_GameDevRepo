using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cloudGeneratorScript : MonoBehaviour
{
    // Start is called before the first frame update
    [SerializeField] List<Sprite> clouds;
    [SerializeField] float cloudsPerSecond = 4.0f;
    [SerializeField] GameObject cloudPrefab;
    [SerializeField] float minCloudSize = 0.75f;
    [SerializeField] float maxCloudSize = 1.5f;
    private bool spawningCloud;
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(!spawningCloud) {
            StartCoroutine("spawnCloud");
        }
    }

    IEnumerator spawnCloud() {
        spawningCloud = true;
        
        float timer = 1.0f;
        float cloudIntervals = timer / cloudsPerSecond;
        float timeSinceCloud = 0.0f;
        bool lastSpawnedLeftSide = false;
        while(timer > 0.0f) {

            if(timeSinceCloud < cloudIntervals) {
                timeSinceCloud += Time.deltaTime;
            } else {
                var cloud = Instantiate(cloudPrefab);
                cloud.GetComponent<SpriteRenderer>().sprite = clouds[Random.Range(0, clouds.Count - 1)];
                cloud.GetComponent<Transform>().localScale = Random.Range(minCloudSize, maxCloudSize) * (Vector3.up + Vector3.right);
                cloud.GetComponent<backgroundCloudScript>().cloudSpeed *= cloud.GetComponent<Transform>().localScale.x;
                cloud.GetComponent<SpriteRenderer>().sortingOrder = -(int)cloud.GetComponent<Transform>().localScale.x;
                cloud.AddComponent<PolygonCollider2D>();
                timeSinceCloud = 0.0f;
                // cloud.GetComponent<PolygonCollider2D>().bounds
                        // _collider.size = new Vector3(_sprite.bounds.size.x / transform.lossyScale.x,
                                    //  _sprite.bounds.size.y / transform.lossyScale.y,
                                    //  _sprite.bounds.size.z / transform.lossyScale.z);

                if(lastSpawnedLeftSide && cloud.transform.position.x < 0) {
                    // Random.
                    if(Random.value > 0.5) {
                        transform.position += Camera.main.ViewportToWorldPoint(Vector3.right * 0.5f);
                        lastSpawnedLeftSide = false;
                    }
                }
                else if (cloud.transform.position.x < 0) {
                    lastSpawnedLeftSide = true;
                }
            }

            timer -= Time.deltaTime;
            yield return null;
        }

        spawningCloud = false;
    }
}
