<?php

/**
 * Class KeysValueBuilder
 */
class EntityToolboxInfoKeysBuilder extends EntityToolboxInfoKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'                  => 'keys',
        'up_structure_before_build' => TRUE,
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  public function genDynamicStructure() {
    $structure = array();
    //@todo add check method to ensure key has been built
    $phase      = $this->getPhase();
    $buildPhase = self::PHZ__BUILD;
    if ($phase == $buildPhase) {
      $hookBuilder = $this->getHookBuilder();
      $properties  = $hookBuilder->getBuild('properties');
      foreach ($properties as $property => $info) {
        if (!empty($info['key'])) {
          $structure[$info['key']] = array(
            'type'    => 'string',
            'default' => $property,
          );
        }
      }
    }

    return $structure;
  }
}