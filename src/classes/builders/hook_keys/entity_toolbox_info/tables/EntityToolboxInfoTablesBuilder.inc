<?php

/**
 * Class TablesBuilder
 */
class EntityToolboxInfoTablesBuilder extends EntityToolboxInfoKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'    => 'tables',
        'model_class' => 'EntityToolboxInfoTablesModel'
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * @return array
   */
  protected function buildRelationTables() {
    $references = array();
    $properties = $this->getHookBuilder()
                       ->getBuild('properties');
    foreach ($properties as $property => $info) {
      if (!empty($info['tables']['relation'])) {
        $references[$property] = $info['tables']['relation'];
      }
    }

    return $references;
  }

  /**
   * @return array
   */
  protected function buildRelationRevisionTables() {
    $references = array();
    $properties = $this->getHookBuilder()
                       ->getBuild('properties');
    foreach ($properties as $property => $info) {
      if (!empty($info['tables']['relation_revision'])) {
        $references[$property] = $info['tables']['relation_revision'];
      }
    }

    return $references;
  }
}