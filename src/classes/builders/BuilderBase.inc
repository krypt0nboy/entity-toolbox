<?php

require_once ENTITY_TOOLBOX_PATH . '/src/classes/helpers/HelperBase.inc';

/**
 * Class BuilderBase
 *
 * Base class to build data required by drupal available api's.
 */
class BuilderBase {

  use EntityToolboxCommonTraits, TemplatingTraits;
  /**
   * @var string $modelClass
   */
  protected $modelClass;
  /**
   * @var ModelBase $model
   *   The data model.
   */
  protected $model;
  /**
   * @var array $structure
   *   The structure of the array to build.
   */
  protected $structure = array();
  /**
   * @var KeyBuilder[] $keyBuilders
   *   The structure keys builders.
   */
  protected $keyBuilders = array();
  /**
   * @var array $keyBuildersClasses
   *   An array of key builder classes.
   */
  protected $keyBuildersClasses = array();
  /**
   * @var array $keyBuildersArgs
   *   An array containing the key builders args.
   *   Key Builders will be instanciated using those args.
   *   - KEY :
   *    - class :
   */
  protected $keyBuildersArgs = array();
  /**
   * @var EntityToolboxHelperBase[] $helpers
   */
  protected $helpers = array();
  /**
   * @var integer $phase
   *   The building phase :
   *   - PHZ__INIT : Initializing the builder.
   *   - PHZ__PREP : Preparing the builder.
   *   - PHZ__BUILD : Building.
   *   - PHZ__REBUILD : Rebuilding.
   *   - PHZ__VED : Validating the build/rebuild.
   *   - PHZ__DELIVER : Delivering.
   */
  protected $phase;
  /**
   * @const PHZ__INIT
   */
  const PHZ__INIT = 0x001;
  /**
   * @const PHZ__PREP
   */
  const PHZ__PREP = 0x002;
  /**
   * @const PHZ__BUILD
   */
  const PHZ__BUILD = 0x003;
  /**
   * @const PHZ__REBUILD
   */
  const PHZ__REBUILD = 0x004;
  /**
   * @const PHZ__VED
   */
  const PHZ__VED = 0x005;
  /**
   * @const PHZ__DELIVER
   */
  const PHZ__DELIVER = 0x006;
  /**
   * @var bool $upStructureBeforeBuild
   *   Indicates if the builder structure needs to be updated before building.
   */
  protected $upStructureBeforeBuild;
  /**
   * @var boolean $ready2Prepare
   *   Is the builder ready to prepare.
   */
  protected $ready2Prepare;
  /**
   * @var boolean $ready2GenerateKeyBuilders
   *   Is the builder ready to generate KeyBuilders.
   */
  protected $ready2GenerateKeyBuilders;
  /**
   * @var boolean $ready2Build
   *   Is the builder ready to build.
   */
  protected $ready2Build;
  /**
   * @var bool $ready2Rebuild
   *   Is the builder ready to rebuild.
   */
  protected $ready2Rebuild;
  /**
   * @var boolean $ready2Deliver
   *   Is the builder ready to deliver.
   */
  protected $ready2Deliver;
  /**
   * @var bool $initialized
   */
  protected $initialized;
  /**
   * @var bool $prepared
   */
  protected $prepared;
  /**
   * @var bool $built
   */
  protected $built;
  /**
   * @var bool $validated
   */
  protected $validated;
  /**
   * @var bool $rebuilt
   */
  protected $rebuilt;
  /**
   * @var bool $delivered
   */
  protected $delivered;
  /**
   * @var array $build
   */
  protected $build = array();

  /*** INIT ***/

  /**
   * BuilderBase constructor.
   *
   * @param array $args
   *   The properties to set.
   *
   * @throws EntityToolboxException
   */
  public function __construct(array $args = array()) {
    $this->setUp($args);
  }

  /**
   * Set up function.
   * Sets the object, and ensures he is ready to build.
   *
   * @param array $args
   *   The args to provide for the builder.
   */
  protected function setUp($args = array()) {
    $this->constructSet($args);
    $this->autoSet();
    $this->prepare();
  }

  /**
   * Init phase where construct args are set.
   *
   * @param array $args
   */
  protected function constructSet($args) {
    $this->setPhase(self::PHZ__INIT);
    $this->setConstructArgs($args);
    $this->bulkSet($args);
  }

  /**
   * Auto sets properties.
   */
  protected function autoSet() {
  }

  /*** INIT END ***/

  /*** SETTERS AND GETTERS ***/

  /**
   * Returns the Model class.
   *
   * @return string
   */
  public function getModelClass() {
    return $this->modelClass;
  }

  /**
   * Sets the Model class.
   *
   * @param string $modelClass
   */
  protected function setModelClass($modelClass) {
    $this->modelClass = $modelClass;
  }

  /**
   * @return ModelBase
   */
  public function getModel() {
    return $this->model;
  }

  /**
   * @param ModelBase $model
   */
  protected function setModel($model) {
    $this->model = $model;
  }

  /**
   * @param $modelClass
   * @param $args
   *
   * @return ModelBase
   */
  protected function modelGetInstance($modelClass, array $args = array()) {
    return new $modelClass($args);
  }

  /**
   * Gets the data structure.
   *
   * @param string $key
   *   A key.
   *
   * @return array
   */
  public function getStructure($key = NULL) {
    return isset($key) ? $this->structure[$key] : $this->structure;
  }

  /**
   * @param array $structure
   */
  protected function setStructure(array $structure = array()) {
    foreach ($structure as $key => $params) {
      $this->structure[$key] = $params;
    }
  }

  /**
   * Returns the build.
   *
   * @param string $key
   *   A key name.
   *
   * @return array
   */
  public function getBuild($key) {
    return isset($key) ? $this->build[$key] : $this->build;
  }

  /**
   * Sets the build.
   *
   * @param array $build
   *   The build to set.
   */
  public function setBuild($build) {
    $this->build = $build;
  }

  /**
   * @param $key
   * @param $build
   *
   * @return array
   */
  protected function setKeyBuild($key, $build) {
    $this->build[$key] = $this->validateKeyBuild($key, $build);
    $this->postBuildKey($key);

    return $this->build[$key];
  }

  /**
   * @return array
   */
  public function getKeyBuildersArgs() {
    return $this->keyBuildersArgs;
  }

  /**
   * @param array $keyBuildersArgs
   */
  public function setKeyBuildersArgs($keyBuildersArgs) {
    $this->keyBuildersArgs = $keyBuildersArgs;
  }

  /**
   * @return BuilderBase[]
   */
  public function getKeyBuilders() {
    return $this->keyBuilders;
  }

  /**
   * @param $key
   * @return \BuilderBase
   */
  public function getKeyBuilder($key) {
    return $this->keyBuilders[$key];
  }

  /**
   * @param BuilderBase[] $keyBuilders
   */
  protected function setKeyBuilders($keyBuilders) {
    foreach ($keyBuilders as $key => $keyBuilder) {
      $this->setKeyBuilder($key, $keyBuilder);
    }
  }

  /**
   * Sets the builder for a given key.
   *
   * @param string            $key
   *   The key name.
   * @param \BuilderBase|NULL $builder
   *   The builder.
   */
  protected function setKeyBuilder($key, BuilderBase $builder = NULL) {
    $this->keyBuilders[$key] = $builder;
  }

  /**
   * @return array
   */
  public function getKeyBuildersClasses() {
    return $this->keyBuildersClasses;
  }

  /**
   * @param array $keyBuildersClasses
   */
  protected function setKeyBuildersClasses($keyBuildersClasses) {
    $this->keyBuildersClasses = $keyBuildersClasses;
  }

  /**
   * @return EntityToolboxHelperBase[]
   */
  public function getHelpers() {
    return $this->helpers;
  }

  /**
   * @param EntityToolboxHelperBase[] $helpers
   */
  public function setHelpers($helpers) {
    $this->helpers = $helpers;
  }

  /**
   * Returns the builds current phase.
   *
   * @return int
   */
  public function getPhase() {
    return $this->phase;
  }

  /**
   * Sets the builder current phase.
   *
   * @param int $phase
   *   The phase to set.
   */
  protected function setPhase($phase) {
    $this->phase = $phase;
  }

  /**
   * @return boolean
   */
  public function isReady2Prepare() {
    return $this->ready2Prepare;
  }

  /**
   * @param boolean $ready2Prepare
   */
  public function setReady2Prepare($ready2Prepare) {
    $this->ready2Prepare = $ready2Prepare;
  }

  /**
   * @return boolean
   */
  public function isReady2GenerateKeyBuilders() {
    if (is_bool($this->ready2GenerateKeyBuilders)) {
      return $this->ready2GenerateKeyBuilders;
    }
    else {
      $eval = $this->evalReady2GenerateKeyBuilders();
      $this->setReady2GenerateKeyBuilders($eval);
    }

    return $this->ready2GenerateKeyBuilders;
  }

  /**
   * @param boolean $ready2GenerateKeyBuilders
   */
  public function setReady2GenerateKeyBuilders($ready2GenerateKeyBuilders) {
    $this->ready2GenerateKeyBuilders = $ready2GenerateKeyBuilders;
  }

  /**
   * @return boolean
   */
  public function isReady2Build() {
    return $this->ready2Build;
  }

  /**
   * @param boolean $ready2Build
   */
  public function setReady2Build($ready2Build) {
    $this->ready2Build = $ready2Build;
  }

  /**
   * @return boolean
   */
  public function isReady2Rebuild() {
    return $this->ready2Rebuild;
  }

  /**
   * @param boolean $ready2Rebuild
   */
  public function setReady2Rebuild($ready2Rebuild) {
    $this->ready2Rebuild = $ready2Rebuild;
  }

  /**
   * @return boolean
   */
  public function isReady2Deliver() {
    return $this->ready2Deliver;
  }

  /**
   * @param boolean $ready2Deliver
   */
  public function setReady2Deliver($ready2Deliver) {
    $this->ready2Deliver = $ready2Deliver;
  }

  /**
   * @return boolean
   */
  public function isInitialized() {
    return $this->initialized;
  }

  /**
   * @param boolean $initialized
   */
  public function setInitialized($initialized) {
    $this->initialized = $initialized;
  }

  /**
   * @return boolean
   */
  public function isPrepared() {
    return $this->prepared;
  }

  /**
   * @param boolean $prepared
   */
  public function setPrepared($prepared) {
    $this->prepared = $prepared;
  }

  /**
   * @return boolean
   */
  public function isBuilt() {
    return $this->built;
  }

  /**
   * @param boolean $built
   */
  public function setBuilt($built) {
    $this->built = $built;
  }

  /**
   * @return boolean
   */
  public function isValidated() {
    return $this->validated;
  }

  /**
   * @param boolean $validated
   */
  public function setValidated($validated) {
    $this->validated = $validated;
  }

  /**
   * @return boolean
   */
  public function isRebuilt() {
    return $this->rebuilt;
  }

  /**
   * @param boolean $rebuilt
   */
  public function setRebuilt($rebuilt) {
    $this->rebuilt = $rebuilt;
  }

  /**
   * @return boolean
   */
  public function isDelivered() {
    return $this->delivered;
  }

  /**
   * @param boolean $delivered
   */
  public function setDelivered($delivered) {
    $this->delivered = $delivered;
  }

  /**
   * @return boolean
   */
  public function getUpStructureBeforeBuild() {
    return $this->upStructureBeforeBuild;
  }

  /**
   * @param boolean $upStructureBeforeBuild
   */
  public function setUpStructureBeforeBuild($upStructureBeforeBuild) {
    $this->upStructureBeforeBuild = $upStructureBeforeBuild;
  }

  /*** SETTERS AND GETTERS END ***/

  /*** EVAL METHODS ***/

  /**
   * Indicates if the builder requires its structure to be updated before building.
   *
   * @return bool
   */
  protected function requiresStructureUp() {
    $eval = $this->__isset('upStructureBeforeBuild') ? $this->getUpStructureBeforeBuild() : FALSE;

    return $eval;
  }

  /**
   * Evaluates if key builders can be generated.
   *
   * @param bool $autoSet
   *   A boolean indicating if property ready2GenerateKeyBuilders should be set.
   *
   * @return boolean
   */
  protected function evalReady2GenerateKeyBuilders($autoSet = FALSE) {
    $eval     = array();
    $required = array(
      'keyBuildersClasses',
      'keyBuildersArgs'
    );
    foreach ($required as $property) {
      $eval[] = $this->__isset($property);
    }

    if (in_array(FALSE, $eval, TRUE)) {
      if ($autoSet) {
        $this->setReady2GenerateKeyBuilders(FALSE);
      }

      return FALSE;
    }
    elseif (in_array(TRUE, $eval, TRUE)) {
      if ($autoSet) {
        $this->setReady2GenerateKeyBuilders(TRUE);
      }

      return TRUE;
    }
    if ($autoSet) {
      $this->setReady2GenerateKeyBuilders(FALSE);
    }

    return FALSE;
  }

  /*** EVAL METHODS ENDS ***/

  /**
   * Returns an instance of a helper.
   *
   * @param string $helperClass
   * @param array  $args
   *
   * @return HelperBase
   */
  protected function helperGetInstance($helperClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'data_holder' => $this,
    ), $args);

    return new $helperClass($args);
  }

  /**
   * Returns an instance of a KeyBuilder.
   *
   * @param string $keyBuilderClass
   *   The key builder class.
   * @param array  $args
   *   The args to pass to the key builder instance.
   *
   * @return mixed
   */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'parent_builder' => $this,
    ), $args);

    return new $keyBuilderClass($args);
  }

  /**
   * Returns the builders key that require a rebuild.
   *
   * @return KeyBuilder[]
   */
  protected function keyBuildersRequireRebuild() {
    $require = array();
    foreach ($this->keyBuilders as $key => $keyBuilder) {
      if ($keyBuilder->getRequiresRebuild()) {
        $require[] = $keyBuilder;
      }
    }

    return $require;
  }

  /*** PREPARE ***/

  /**
   * Prepares the builder structure and components.
   */
  protected function prepare() {
    $this->setPhase(self::PHZ__PREP);
    $this->initTemplateVars();
    $this->generateModel();
    $this->generateHelpers();
    $this->prepareStructure();
    $this->generateComponents();
    $this->alterStructure();
  }

  /**
   * Prepares the structure.
   */
  protected function prepareStructure() {
    $method    = isset($this->model) ? 'genStructureFromModel' : 'genDynamicStructure';
    $structure = $this->$method();
    $this->__set('structure', $structure);
  }

  /**
   * Generates the structure from the model's structure.
   *
   * @return array
   */
  protected function genStructureFromModel() {
    $structure = $this->getModel()->getStructure();

    return $structure;
  }

  /**
   * Generates and set a dynamic structure.
   *
   * @return array
   */
  protected function genDynamicStructure() {
  }

  /**
   * Re generates and set a dynamic structure.
   *
   * @return array
   */
  protected function reGenDynamicStructure() {
    return $this->genDynamicStructure();
  }

  /**
   * Updates structure before building.
   */
  protected function upStructure() {
    $structure = $this->reGenDynamicStructure();
    if (!empty($structure)) {
      $this->__set('structure', $structure);
    }
  }

  /**
   * Alters the structure.
   */
  protected function alterStructure() {
  }

  /**
   * Initialize the template variables.
   *
   * @param array $vars
   *   The variables to init.
   *
   * @return array
   */
  protected function initTemplateVars(array $vars = array()) {
    $this->setTemplateVars($vars);
  }

  /**
   * Instanciates the required object properties.
   */
  protected function generateComponents() {
    $this->generateKeyBuilders();
  }

  /**
   * Generate and adds required helpers.
   */
  protected function generateHelpers() {

  }

  /**
   * Get KeyBuilder instances for each structure key.
   */
  protected function generateKeyBuilders() {
    foreach ($this->keyBuildersClasses as $key => $class) {
      $args = !empty($this->keyBuildersArgs[$key]) ? $this->keyBuildersArgs[$key] : array();
      $args += array(
        'self_key' => $key,
      );
      $this->setKeyBuilder($key, $this->keyBuilderGetInstance($class, $args));
    }
  }

  /**
   * Instanciates and sets a Model instance.
   */
  protected function generateModel() {
    if (isset($this->modelClass)) {
      $this->__set('model', $this->modelGetInstance($this->modelClass));
    }
  }

  /**
   * Called before build.
   */
  protected function preBuild() {
    if ($this->requiresStructureUp()) {
      $this->upStructure();
    }
  }

  /*** PREPARE END ***/

  /**
   * Return the built/rebuilt data.
   *
   * @return mixed
   */
  public function build() {
    $this->setPhase(self::PHZ__BUILD);
    $this->preBuild();
    $this->buildDefault();
    $this->validateBuild();
    $this->postBuild();

    return $this->deliver();
  }

  /**
   * Default build function.
   *
   * @return array
   */
  protected function buildDefault() {
    foreach (array_keys($this->structure) as $key) {
      $this->buildKey($key);
    }
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
      if (is_null($build) && isset($this->structure[$key]['default'])) {
        return $this->buildKeyDefault($key);
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

  /**
   * Default build method for a given key.
   *
   * @param string $key
   *   The key name.
   *
   * @return mixed
   */
  protected function buildKeyDefault($key) {
    $default = $this->structure[$key]['default'];
    $build   = $this->processValueTemplate($default);

    return $this->setKeyBuild($key, $build);
  }

  /**
   * Called after the key data has been built.
   *
   * @param string $key
   *   The key name.
   */
  protected function postBuildKey($key) {
    $this->updateKeyBuildTemplateVars($key);
    $this->postBuildKeyMethod($key);
  }

  /**
   * Updates the template vars from a key build.
   *
   * @param string $key
   * @param null   $replaceMarker
   */
  protected function updateKeyBuildTemplateVars($key, $replaceMarker = NULL) {
    $replaceMarker = isset($replaceMarker) ? $replaceMarker : '';
    $extract       = array($key => $this->build[$key]);
    $flattened     = $this->flattenExtract('', $replaceMarker, $extract);
    $this->updateTemplateVars($flattened);
  }

  /**
   * Calls custom post key build method.
   *
   * @param string $key
   *   The key name.
   */
  protected function postBuildKeyMethod($key) {
    $uKey   = lowercase2camelcase($key);
    $method = "postBuild$uKey" . "Key";
    if (method_exists($this, $method)) {
      $this->$method($uKey);
    }
  }

  /**
   * Method called after the build has been set,
   * and before it is delivered.
   */
  protected function postBuild() {

  }

  /**
   * Rebuilds a key value.
   *
   * @param string $key
   *   The key name.
   *
   * @return mixed
   */
  protected function rebuildKey($key) {
    return $this->buildKey($key);
  }

  /**
   * Returns the build.
   *
   * @return array
   */
  protected function deliver() {
    $this->isReady2DeliverEval();
    if ($this->isReady2Deliver()) {
      return $this->build;
    }
    else {
      $this->deliverFailFix();

      return $this->build;
    }
  }

  /**
   * Evaluates if the build is ready to be delivered.
   * Sets ready2Deliver.
   */
  protected function isReady2DeliverEval() {
    $eval = array();
    foreach ($this->getKeyBuilders() as $key => $keyBuilder) {
      $eval[] = $keyBuilder->isReady2Deliver();
    }

    if (in_array(FALSE, $eval, TRUE)) {
      $this->setReady2Deliver(FALSE);
    }
    elseif (in_array(TRUE, $eval, TRUE)) {
      $this->setReady2Deliver(TRUE);
    }
  }

  /**
   * Calls fix methods when deliverEval has failed.
   */
  protected function deliverFailFix() {
    $failed = array();
    foreach ($this->getKeyBuilders() as $key => $keyBuilder) {
      if (!$keyBuilder->isReady2Deliver()) {
        $failed[$key] = $keyBuilder;
      }
    }
    foreach ($failed as $key => $keyBuilder) {

    }
  }

  /**
   * @param $value
   * @return string
   */
  protected function processValueTemplate($value) {
    return $this->isValueTemplate($value) ? string_template_process($value, $this->getTemplateVars()) : $value;
  }

  /**
   * Validates the build before it can be delivered.
   */
  protected function validateBuild() {
    $this->unsetKeysEval();
    uasort($this->build, 'drupal_sort_weight');
  }

  /**
   * Validates a key build.
   *
   * @param string $key
   *   The key.
   * @param mixed  $build
   *   The build to validate.
   *
   * @return bool
   */
  protected function validateKeyBuild($key, $build) {
    $type      = $this->getStructure($key)['type'];
    $buildType = gettype($build);

    if (!preg_match('/\|/', $type)) {
      $cType     = lowercase2camelcase($type);
      $vedMethod = 'validate' . $cType . 'Value';
      if (method_exists($this, $vedMethod)) {
        $build = $this->$vedMethod($build, $buildType);
      }
    }
    else {
      $build = $this->validateMixedValue($build, $buildType, $type);
    }

    $cKey   = lowercase2camelcase($key);
    $method = 'validate' . $cKey;
    if (method_exists($this, $method)) {
      $build = $this->$method($build);
    }

    return $build;
  }

  /**
   * @param $valueType
   * @param $matchType
   * @return bool
   */
  protected function matchType($valueType, $matchType) {
    return $valueType == $matchType;
  }

  /**
   * @param $value
   * @param $valueType
   * @return mixed
   */
  protected function validateBooleanValue($value, $valueType) {
    $matchType = $this->matchType($valueType, 'boolean');
    if (!$matchType) {
      if ($this->isValueTemplate($value)) {
        $value = FALSE;
      }
      else {
        settype($value, 'boolean');
      }
    }

    return $value;
  }

  /**
   * @param $value
   * @param $valueType
   * @return mixed
   */
  protected function validateIntegerValue($value, $valueType) {
    $matchType = $this->matchType($valueType, 'integer');
    if (!$matchType) {
      if ($this->isValueTemplate($value)) {
        $value = 0;
      }
      else {
        settype($value, 'integer');
      }
    }

    return $value;
  }

  /**
   * @param $value
   * @param $valueType
   * @return mixed
   */
  protected function validateDoubleValue($value, $valueType) {
    $matchType = $this->matchType($valueType, 'double');
    if (!$matchType) {
      if ($this->isValueTemplate($value)) {
        $value = 0;
      }
      else {
        settype($value, 'double');
      }
    }

    return $value;
  }

  /**
   * @param $value
   * @param $valueType
   * @return mixed
   */
  protected function validateStringValue($value, $valueType) {
    $matchType = $this->matchType($valueType, 'string');
    if (!$matchType) {
      settype($value, 'string');
    }

    return $value;
  }

  /**
   * @param $value
   * @param $valueType
   * @return mixed
   */
  protected function validateArrayValue($value, $valueType) {
    $matchType = $this->matchType($valueType, 'array');
    if (!$matchType) {
      $value = array();
    }

    return $value;
  }

  /**
   * @param $value
   * @param $valueType
   * @return mixed
   */
  protected function validateObjectValue($value, $valueType) {
    $matchType = $this->matchType($valueType, 'object');

    return $value;
  }

  /**
   * @param $value
   * @param $valueType
   * @return mixed
   */
  protected function validateNullValue($value, $valueType) {
    $matchType = $this->matchType($valueType, 'null');
    if (!$matchType) {
      settype($value, 'null');
    }

    return $value;
  }

  /**
   * @param      $value
   * @param      $valueType
   * @param null $mixed
   * @return mixed
   */
  protected function validateMixedValue($value, $valueType, $mixed = NULL) {
    if (isset($mixed)) {
      $types     = explode('|', $mixed);
      $matchType = in_array($valueType, $types);
      if (!$matchType) {
        if ($this->isValueTemplate($value)) {
          $value = '';
        }
        settype($value, $types[0]);
      }
    }

    return $value;
  }

  /**
   * Evaluates if a key build should be unset from the build.
   */
  protected function unsetKeysEval() {
    $keys = array_flip(array_keys($this->build));
    $mod  = 0;
    foreach ($this->build as $key => $value) {
      $unset = $this->unsetKeyEval($key, $value);
      if ($unset) {
        $pos = $keys[$key] - $mod;
        array_splice($this->build, $pos, 1);
        $mod++;
      }
    }
  }

  /**
   * @param $key
   * @param $build
   * @return bool
   */
  protected function unsetKeyEval($key, $build) {
    $proceed = isset($this->getStructure($key)['unset if']);
    $eval    = FALSE;
    if ($proceed) {
      $unsetIf = $this->getStructure($key)['unset if'];
      $negate  = preg_match('/^!\w+/', $unsetIf);
      $unsetIf = $negate ? preg_replace('/^!/', '', $unsetIf) : $unsetIf;
      switch ($unsetIf) {
        case 'false':
          $eval = $build == FALSE;
          break;
        case 'true':
          $eval = $build == TRUE;
          break;
        default:
          $isCallback = preg_match('/(?P<callback>.+)(:c:)$/', $unsetIf, $matches);
          if ($isCallback) {
            $isCallable = is_callable($matches['callback']);
            $eval       = $isCallable ? $matches['callback']($build) : $build == $unsetIf;
          }
          else {
            $eval = $build == $unsetIf;
          }
          break;
      }

      return $negate ? !$eval : $eval;
    }
    else {
      return $eval;
    }
  }
}