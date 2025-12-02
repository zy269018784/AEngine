#ifdef PROJECT_USE_ALSA
#include <alsa/asoundlib.h>
#include <alsa/control.h>
#endif
#include <stdio.h>

#include  "Audio/AdvancedLinuxSoundArchitecture/ALSADevice.h"
#include  "Audio/AdvancedLinuxSoundArchitecture/ALSAElementList.h"
#include  "Audio/AdvancedLinuxSoundArchitecture/ALSAControl.h"
#include  "Audio/AdvancedLinuxSoundArchitecture/ALSAElementInfo.h"
#include  "Audio/AdvancedLinuxSoundArchitecture/ALSACardInfo.h"

void list_alsa_devices() ;
int TestAlsa()
{
#ifdef PROJECT_USE_ALSA
    list_alsa_devices();
    int error;

    int card_index = -1;
    char *name;
    char *lone_name;
    while (1)
    {
        error = snd_card_next(&card_index);
        if (error)
            printf("snd_card_next %d\n", error);
        if (-1 == card_index)
            break;

        ALSADevice Device(card_index);
        printf("card_index %d: [%s], [%s]\n", Device.GetHandle(), Device.GetName(), Device.GetLongName());
    }

    ALSAControl* Ctrl = new ALSAControl;
    ALSAElementList *List = new ALSAElementList;
    ALSAElementInfo *Eleminfo = new ALSAElementInfo;
    ALSACardInfo *CardInfo = new ALSACardInfo;
    error =  Ctrl->Open("default", SND_CTL_ASYNC);
    if (error)
        printf("isnd_ctl_open %d\n", error);

    printf("ctrl name %s\n", Ctrl->Name());

    /*
     * Get Card Info
     */
    Ctrl->CardInfo(CardInfo->Handle);
    printf("CardInfo name %s\n", CardInfo->Name());

    /*
     * Get Element List
     */
    Ctrl->ElementList(List->Handle);

    unsigned int ListCount = List->GetCount();
    printf("ListCount %d\n", ListCount);

    // list alloc space
    List->AllocSpace(ListCount);

    // list set offet
    List->SetOffset(0);

    /*
     * Get Element List
     */
    Ctrl->ElementList(List->Handle);

    printf("Elements:\n");
    for (unsigned int i = 0; i < ListCount; i++)
    {
        printf("\t%s\n", List->GetName(i));
    }


    //Ctrl->ElementInfo(Eleminfo->Handle);
   // printf("eleminfo name %s\n", Eleminfo->Name());

    delete Eleminfo;
    delete List;
    delete Ctrl;
#endif
    return 0;
}

void list_alsa_devices() {
#ifdef PROJECT_USE_ALSA
    char** hints;
    int err;

    err = snd_device_name_hint(-1, "pcm", (void***)&hints);
    if (err != 0) {
        fprintf(stderr, "Error: Cannot get device hints: %s\n", snd_strerror(err));
        return;
    }

    char** n = hints;
    int count = 0;

    while (*n != NULL) {
        char* name = snd_device_name_get_hint(*n, "NAME");
        char* desc = snd_device_name_get_hint(*n, "DESC");
        char* ioid = snd_device_name_get_hint(*n, "IOID");

        if (name && strcmp(name, "null") != 0) {
            printf("Device #%d:\n", ++count);
            printf("  Name: %s\n", name);

            if (desc) {
                // Clean up description
                char* clean_desc = strdup(desc);
                char* p = clean_desc;
                while (*p) {
                    if (*p == '\n') *p = ' ';
                    p++;
                }
                printf("  Desc: %s\n", clean_desc);
                free(clean_desc);
            }

            if (ioid) {
                printf("  I/O: %s\n", ioid);
            }
            printf("\n");
        }

        if (name) free(name);
        if (desc) free(desc);
        if (ioid) free(ioid);
        n++;
    }

    snd_device_name_free_hint((void**)hints);

    if (count == 0) {
        printf("No ALSA devices found!\n");
    }
#endif
}
