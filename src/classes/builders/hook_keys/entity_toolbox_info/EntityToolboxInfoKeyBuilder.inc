<?php

/**
 * Class EntityToolboxInfoValueBuilder
 */
class EntityToolboxInfoKeyBuilder extends EntityDependentHookKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'entity_toolbox_info',
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  public function entityGetInfo($entityType) {
    if ($entityType != $this->entityType) {
      return $this->entityGetCachedInfo($entityType);
    }
    else {
      return $this->getBuild('entity_info');
    }
  }

  /** {{@inheritdoc}} */
  protected function postBuildKey($key) {
    parent::postBuildKeyMethod($key);
  }

}