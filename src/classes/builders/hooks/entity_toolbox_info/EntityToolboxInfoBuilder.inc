<?php

require_once ENTITY_TOOLBOX_PATH . '/src/classes/builders/hook_keys/entity_info/AdminUIBuilder.inc';

/**
 * Class EntityToolboxInfoBuilder
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilder extends EntityDependentHookBuilder {
  /**
   * @var array $rawData
   */
  protected $rawData = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook'                 => 'entity_toolbox_info',
      'self_extract_marker'  => '',
      'self_replace_marker'  => 'toolbox_info_',
      'key_builders_classes' => array(
        'labels'    => 'EntityToolboxInfoLabelsBuilder',
        'tables'    => 'EntityToolboxInfoTablesBuilder',
        'callbacks' => 'EntityToolboxInfoCallbacksBuilder',
        'keys'      => 'EntityToolboxInfoKeysBuilder',
      )
    ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractTemplateVars($this->rawData, '', 'toolbox_info_');
    $vars += array('toolbox_info_entity_type' => $this->entityType);
    $vars += array(
      'toolbox_info_module_path' =>
        drupal_get_path('module', $this->rawData['module'])
    );
    parent::initTemplateVars($vars);
  }

  /**
   * @param string $key
   * @return array
   */
  public function getRawData($key = NULL) {
    if (isset($key)) {
      if (!empty($this->rawData[$key])) {
        return $this->rawData[$key];
      }
      else {
        $type = $this->getStructure($key)['type'];
        if ($type == 'array') {
          return array();
        }
      }
    }
    else {
      return $this->rawData;
    }
  }

  /**
   * @param array $rawData
   */
  public function setRawData($rawData) {
    $this->rawData = $rawData;
  }

  /**
   * @param null $property
   * @return array
   */
  public function getRawProperties($property = NULL) {
    if (!empty($this->rawData['properties'])) {
      return isset($property) ? !empty($this->rawData['properties'][$property]) ? $this->rawData['properties'][$property] : array() : $this->rawData['properties'];
    }
    else {
      return array();
    }
  }

  /**
   * Returns the raw operations.
   *
   * @return array
   */
  public function getRawOperations() {
    return !empty($this->rawData['operations']) ? $this->rawData['operations'] : array();
  }

  /**
   * After raw data has been set.
   */
  protected function postSetRawData() {
    if (isset($this->rawData['group'])) {
      $this->__set('group_name', $this->rawData['group']);
    }
  }

  /** {{@inheritdoc}} */
  protected function setKeyBuild($key, $build) {
    return parent::setKeyBuild($key, $build);
  }

  /**
   * Builds the value for a given key.
   *
   * @param string $key
   *   The key to build.
   *
   * @return mixed
   */
  protected function buildKey($key) {
    if (!empty($this->structure[$key]['method'])) {
      $method = $this->structure[$key]['method'];
      $build  = $this->$method();
      if (($this->getStructure($key)['type'] == 'array')) {
        if (!empty($this->rawData[$key])) {
          return $this->setKeyBuild($key, array_replace_recursive($build, $this->rawData[$key]));
        }
        else {
          return $this->setKeyBuild($key, $build);
        }
      }
      else {
        return $this->setKeyBuild($key, $build);
      }
    }
    else {
      if (isset($this->structure[$key]['default'])) {
        return $this->buildKeyDefault($key);
      }
    }
  }

  /** {{@inheritdoc}} */
  protected function updateKeyBuildTemplateVars($key, $replaceMarker = NULL) {
    parent::updateKeyBuildTemplateVars($key, 'toolbox_info_');
  }

  /**
   * Builds the root path.
   *
   * @return string
   */
  protected function buildRootPath() {
    if (($group = $this->getBuild('group')) && isset($group)) {
      return $this->processValueTemplate('%group_info_path%/%toolbox_info_labels_machine_name_plural%');
    }
    else {
      return $this->processValueTemplate('admin/structure/%toolbox_info_labels_machine_name_plural%');
    }
  }

  /**
   * Builds the labels.
   *
   * @return array
   */
  protected function buildLabels() {
    $build = $this->getKeyBuilder('labels')->build();

    return $build;
  }

  /**
   * Builds has_revisions.
   */
  protected function buildHasRevisions() {
  }

  /**
   * Builds has_translations.
   */
  protected function buildHasTranslations() {
  }

  /**
   * Builds exportable.
   */
  protected function buildExportable() {
  }

  /**
   * Builds the classes.
   *
   * @return array
   */
  protected function buildClasses() {
    return $this->getKeyBuilder('classes')->build();
  }

  /**
   * Builds the properties.
   *
   * @return array
   */
  protected function buildProperties() {
    return $this->getKeyBuilder('properties')->build();
  }

  /**
   * Builds the tables.
   *
   * @return string
   */
  protected function buildTables() {
    $tables = $this->getKeyBuilder('tables')->build();
    if (!$this->getBuild('has_revisions')) {
      $tables['revision'] = NULL;
      if (!empty($tables['relation_revision'])) {
        $tables['relation_revision'] = array();
      }
    }

    return $tables;
  }

  /**
   * Builds the callbacks.
   *
   * @return array
   */
  protected function buildCallbacks() {
    return $this->getKeyBuilder('callbacks')->build();
  }

  /**
   * Builds the operations.
   *
   * @return array
   */
  protected function buildOperations() {
    return $this->getKeyBuilder('operations')->build();
  }

  /**
   * Builds the keys.
   *
   * @return array
   */
  protected function buildKeys() {
    return $this->getKeyBuilder('keys')->build();
  }

  /**
   * Builds the children_inherit.
   *
   * @return array
   */
  protected function buildChildrenInherit() {
    $inherit = array();
    foreach ($this->getBuild('properties') as $property => $info) {
      if ($info['children_inherit'] === TRUE) {
        $inherit[] = $property;
      }
    }

    return $inherit;
  }

  /**
   * Builds the group.
   *
   * @return string
   */
  protected function buildGroup() {
  }

  protected function buildEntityInfo() {
    $instanceArgs = array(
      'entity_type'  => $this->entityType,
      'toolbox_info' => $this->build,
      'module'       => $this->module,
    );
    $factoryArgs  = array(
      'entity_type'   => $this->entityType,
      'toolbox_info'  => $this->build,
      'instance_args' => $instanceArgs,
    );
    $builder      = hook_get_builder('entity_info', $factoryArgs);

    return $builder->build();
  }
}