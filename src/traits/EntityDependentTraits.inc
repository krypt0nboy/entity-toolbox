<?php

/**
 * Class EntityDependentTraits
 */
trait EntityDependentTraits {
  /**
   * @var string $entityType
   */
  public $entityType;
  /**
   * @var bool $fieldable
   */
  public $fieldable;

  /**
   * @return string
   */
  public function getEntityType() {
    return $this->entityType;
  }

  /**
   * @param string $entityType
   */
  public function setEntityType($entityType) {
    $this->entityType = $entityType;
  }

  /**
   * @return boolean
   */
  public function getFieldable() {
    return $this->fieldable;
  }

  /**
   * @param boolean $fieldable
   */
  public function setFieldable($fieldable) {
    $this->fieldable = $fieldable;
  }

  /**
   * @param $entityType
   * @return array
   */
  public function entityGetCachedInfo($entityType) {
    global $language;
    if (is_entity_toolbox_entity($entityType)) {
      if ($this->entityType != $entityType) {
        $cache = entity_toolbox_cache_get(ENTITY_TOOLBOX__TMP_ENTITY_INFO);
        if (!empty($cache)) {
          $referencesInfo       = $cache->data;
          $toolboxReferenceInfo = $referencesInfo[$entityType];

          return $toolboxReferenceInfo['entity_info'];
        }
      }
      else {
      }
    }
    else {
      $cache = cache_get("entity_info:$language->language");
      if (empty($cache)) {
        $referenceInfo = pre_build_entity_get_info($entityType);
      }
      else {
        $referencesInfo = $cache->data;
        $referenceInfo  = $referencesInfo[$entityType];
      }

      return $referenceInfo;
    }
  }
}