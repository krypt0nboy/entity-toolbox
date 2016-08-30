<?php

/**
 * Class EntityPropertyInfo
 */
class EntityPropertyInfoBuilder extends EntityToolboxDependentHookBuilder {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook'                 => 'entity_property_info',
        'model_class'          => 'EntityPropertyInfoModel',
        'key_builders_classes' => array(
          'properties' => 'EntityPropertyInfoPropertiesBuilder',
          'bundles'    => 'EntityPropertyInfoBundlesBuilder',
        ),
      ),
      $args
    );
    parent::__construct($args);
  }

  public function buildProperties() {
    return $this->getKeyBuilder('properties')->build();
  }

  public function buildBundles() {
    return $this->getKeyBuilder('bundles')->build();
  }
}